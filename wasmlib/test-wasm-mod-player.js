const fs = require('fs');

const NOT_IMPLEMENTED = () => {
    console.error('not implemented');
};
const ptmod = fs.readFileSync('trackerscripting.mod');

async function start() {
    const xmp = await WebAssembly.instantiate(fs.readFileSync('wasm-mod-player.wasm'), {
        "wasi_snapshot_preview1": {
            "fd_close": NOT_IMPLEMENTED,
            "fd_write": NOT_IMPLEMENTED,
            "fd_seek": NOT_IMPLEMENTED,
            "fd_read": NOT_IMPLEMENTED,
            "environ_get": NOT_IMPLEMENTED,
            "environ_sizes_get": NOT_IMPLEMENTED,
            "args_sizes_get": NOT_IMPLEMENTED,
            "args_get": NOT_IMPLEMENTED,
            "proc_exit": NOT_IMPLEMENTED,
        },
        "env": {
            "round": (num) => Math.round(num),
            "__syscall221": NOT_IMPLEMENTED,
            "__syscall5": NOT_IMPLEMENTED,
            "__syscall10": NOT_IMPLEMENTED,
            "__syscall220": NOT_IMPLEMENTED,
            "__syscall60": NOT_IMPLEMENTED,
            "__syscall195": NOT_IMPLEMENTED,
            "__syscall54": NOT_IMPLEMENTED,
            "localtime_r": NOT_IMPLEMENTED,
            "__clock_gettime": NOT_IMPLEMENTED
        }
    });
    
    const memaddr = xmp.instance.exports.allocMemoryForModule(ptmod.byteLength);
    const heap8 = new Uint8Array(xmp.instance.exports.memory.buffer);
    const heap32 = new Uint32Array(xmp.instance.exports.memory.buffer);
    heap8.set(ptmod, memaddr);
    xmp.instance.exports.loadModule(memaddr, ptmod.byteLength, 44100);
    
    for(var f=0; f<1024; f++) {
        const frameinfo = xmp.instance.exports.playFrame();
        const bufptr = heap32[(frameinfo/4) + 10];
        const bufsize = heap32[(frameinfo/4) + 11];
        
        process.stdout.write(heap8.subarray(bufptr, bufptr + bufsize));
    }
}
start();