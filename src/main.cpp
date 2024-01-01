#include <iostream>
#include "Sori.h"
#include "Utils.h"
#include "WASMInclude.h"

#include "Score.h"

int sound_table[256];

using namespace std;

int main()
{
    cout << "MoongMaker v1.0" << endl;
}

Sori::Sori source;

extern "C" EMSCRIPTEN_KEEPALIVE void initialize(double s, double e, int start_val, int end_val)
{
    cout << "start: " << s << ", end: " << e << endl;

    Sori::Sori wave;

    if(!wave.open("source.wav"))
    {
        printf("Failed to open original wav file\n");
        return;
    }

    int start_idx = wave.to_index(s);
    int end_idx = wave.to_index(e);
    
    //while(start_idx < end_idx && wave.get(0, start_idx) < 12800) start_idx++;
    //while(start_idx < end_idx && wave.get(0, end_idx) < 12800) end_idx--;
    
    // moongtange
    //while(start_idx < end_idx && wave.get(0, start_idx) < 4800) start_idx++;
    //while(start_idx < end_idx && wave.get(0, end_idx) < 6000) end_idx--;
    while(start_idx < end_idx && wave.get(0, start_idx) < start_val) start_idx++;
    while(start_idx < end_idx && wave.get(0, end_idx) < end_val) end_idx--;

    cout << "Start idx : " << start_idx << ", End idx : " << end_idx << endl;

    source = Sori::Sori(wave.get_num_channels(), wave.get_bytes_per_sample(), wave.get_sample_rate());

    for(int i=start_idx; i<end_idx; i++)
    {
        int now_ch0 = wave.get(0, i);
        int now_ch1 = wave.get(1, i);
        
        source.channels[0].push_back(now_ch0);
        source.channels[1].push_back(now_ch1);
    }

    source.write("src.wav");
}

// bpm: 출력 파일의 bpm, pitch: 입력 파일에서 조정할 피치
extern "C" EMSCRIPTEN_KEEPALIVE void create_wav(double bpm, double pitch)
{
    for (int i = 0; i < 15; i++)
        sound_table[sound_ch[i]] = i;

    // score.txt
    Sori::Sori wave2(2, 2, source.get_sample_rate());

    double multiplier = bpm/60;
    double wave_idx = 0;

    double speed_ = pow(2, pitch/12);
    
    auto rest = [&](double length) {
        wave_idx = 0;
        for(int i=0; i<source.get_sample_rate() * length / multiplier; i++)
        {
            int now_ch0 = source.get(0, wave_idx);
            int now_ch1 = source.get(1, wave_idx);
            
            wave2.channels[0].push_back(now_ch0);
            wave2.channels[1].push_back(now_ch1);
        }
    };
    auto rest_cnt = [&](int cnt) {
        wave_idx = 0;
        for(int i=0; i<cnt; i++)
        {
            int now_ch0 = source.get(0, wave_idx);
            int now_ch1 = source.get(1, wave_idx);
            
            wave2.channels[0].push_back(now_ch0);
            wave2.channels[1].push_back(now_ch1);
        }
    };
    auto append_sound = [&](int a, double length, int octave = 3) {
        double Hz = 55 * (1 << (octave-1)) * pow((double)1.059463094359295, a);
        double speed = speed_ * Hz / 220;
        
        wave_idx = 0;
        int real_cnt = source.get_sample_rate() * length*0.9 / multiplier;
        for(int i=0; i<real_cnt; i++)
        {
            int now_ch0 = source.get(0, wave_idx);
            int now_ch1 = source.get(1, wave_idx);
            
            wave2.channels[0].push_back(now_ch0);
            wave2.channels[1].push_back(now_ch1);
            
            wave_idx += speed;
            if(wave_idx >= source.channels[0].size())
                wave_idx -= source.channels[0].size();
        }
        
        //rest(length*0.1);
        rest_cnt(source.get_sample_rate() * length / multiplier - real_cnt);
    };

    string score_str;
    Utils::read_all_file(score_str, "score.txt");

    vector<string> score;
    Utils::split(score, score_str, "\n");

    for (auto& str : score)
    {
        Utils::trim(str);

        if (str.size() == 0 || str[0] == '#')
            continue;

        vector<string> sound;
        Utils::split(sound, str, " ");

        int sound_ = sound_table[sound[0][0]];
        if (sound[0].size() == 2)
        {
            sound_ += (sound[0][1] == '#' ? 1 : -1);
        }

        double length = stold(sound[1]);

        if (sound[0] == "rest")
        {
            rest(length);
            continue;
        }
        
        int octave = 3;
        if (sound.size() == 3)
            octave = stoi(sound[2]);

        append_sound(sound_, length, octave);
    }
    
    wave2.write("output.wav");
}