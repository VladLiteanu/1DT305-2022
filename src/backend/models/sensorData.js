var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var sensorDataSchema = new Schema({
    sound: { type: Number},
    analogTemp: { type: Number},
    dhtTemp: { type: Number},
    humidity: { type: Number},
    heatIndex: { type: Number},
    light: { type: Number},
    motion: { type: Number},
    steam: { type: Number},
    time: { type: Date, default: Date.now },
    device: { type: Schema.Types.ObjectId, ref: 'device', required: true },
});

module.exports = mongoose.model('sensorData', sensorDataSchema);
