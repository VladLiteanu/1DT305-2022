var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var sensorDataSchema = new Schema({
    sound: { type: double},
    analogTemp: { type: double},
    dhtTemp: { type: double},
    humidity: { type: double},
    heatIndex: { type: double},
    light: { type: double},
    motion: { type: double},
    steam: { type: double},
    time: { type: Date, default: Date.now },
    device: { type: Schema.Types.ObjectId, ref: 'device', required: true },
});

module.exports = mongoose.model('sensorData', sensorDataSchema);
