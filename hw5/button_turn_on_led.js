var GPIO = require('onoff').Gpio,
    led = new GPIO(27, 'out'),
    button = new GPIO(17, 'in', 'both');

function light(Err, value) {

    if(value == 1) {
        led.writeSync(1);

    }
    else {
        led.writeSync(0);
    }
}

button.watch(light);