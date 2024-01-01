let initialize_button = document.getElementById('initialize-button');
let score_text = document.getElementById('score-text');
let create_wav = document.getElementById('create-wav');
let bpm_input = document.getElementById('bpm');
let pitch_input = document.getElementById('pitch');
let download_button = document.getElementById('download-button');

let reader = new FileReader();

let file_data = undefined;

function load_file() {
    let files = document.getElementById('myfile').files;
    let file=files[0];
    reader.addEventListener('loadend', () => {file_data = new Uint8Array(reader.result)});
    reader.readAsArrayBuffer(file);
}

function load_file_to_wasm(filename, uint8_view){
    //let result=reader.result;
    //const uint8_view = new Uint8Array(result);

    if(uint8_view == undefined)
        return;

    Module.FS.writeFile(filename, uint8_view)
    //Module.ccall('print_file', 'number', ['string'], ['write_test.txt'])
}

function loadWASMAudio(filename) {
    //mime = mime || "application/octet-stream";
    let mime = 'audio/wav';
  
    let content = Module.FS.readFile(filename);
    //console.log(`Offering download of "${filename}", with ${content.length} bytes...`);
  
    let url = URL.createObjectURL(new Blob([content], {type: mime}));
  
    const audio = document.getElementById('audio');
    const source = document.getElementById('source');

    // Insert blob object URL into audio element & play.
    source.src = url;
    audio.load();
}

function offerFileAsDownload(filename, mime) {
    mime = mime || "application/octet-stream";
  
    let content = Module.FS.readFile(filename);
    console.log(`Offering download of "${filename}", with ${content.length} bytes...`);
  
    var a = document.createElement('a');
    a.download = filename;
    a.href = URL.createObjectURL(new Blob([content], {type: mime}));
    a.style.display = 'none';
  
    document.body.appendChild(a);
    a.click();
    setTimeout(() => {
      document.body.removeChild(a);
      URL.revokeObjectURL(a.href);
    }, 2000);
}

initialize_button.onclick = () => {
    load_file();
    load_file_to_wasm('source.wav', file_data);
    Module.ccall('initialize', null, ['number', 'number', 'number', 'number'], [7.4, 7.8, 4800, 6000]);
}

create_wav.onclick = () => {
    //alert(score_text.value);
    let bpm = Number(bpm_input.value);
    let pitch = Number(pitch_input.value);

    var enc = new TextEncoder();
    let file = enc.encode(score_text.value);
    //console.log(file);
    load_file_to_wasm('score.txt', file);

    Module.ccall('create_wav', null, ['number', 'number'], [bpm, pitch]);

    setTimeout(() => loadWASMAudio('output.wav'), 2000);
}

download_button.onclick = () => {
    offerFileAsDownload('output.wav', 'music/wav');
}

fetch(`/moving.wav`, {method: 'GET'})
.then(response => response.blob())
.then(body => body.arrayBuffer())
.then(buffer => {
    let arr = new Uint8Array(buffer);
    load_file_to_wasm('source.wav', arr);
    Module.ccall('initialize', null, ['number', 'number', 'number', 'number'], [7.4, 7.8, 4800, 6000]);
})