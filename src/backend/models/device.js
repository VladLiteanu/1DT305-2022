var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var deviceSchema = new Schema({
    name: { type: String, required: true }
});

module.exports = mongoose.model('device', deviceSchema);
