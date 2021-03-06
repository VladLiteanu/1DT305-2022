var express = require('express')
var router = express.Router()
var SensorData = require('../models/sensorData')

// get all sensorDatas
router.get('/api/sensorDatas', (req, res, next) => {
    SensorData.find((err, sensorDatas) => {
        if (err) {
            return next(err)
        }
        res.json({
            "sensorData": sensorDatas
        })
    })
})

//get one sensorData
router.get('/api/sensorDatas/:id', (req, res, next) => {
    var id = req.params.id
    if (!(id.match(/^[0-9a-fA-F]{24}$/))) {
        return res.status(404).json({
            "message": "Item not found"
        })
    }
    SensorData.findById(id, (err, sensorData) => {
        if (err) {
            return next(err)
        }
        if (sensorData == null) {
            return res.status(404).json({
                "message": "SensorData not found."
            })
        }
        res.json(sensorData)
    })
})

// Get the sensor data from a specific date
router.get('/api/sensorDatas/:date', (req, res, next) => {
    var date = req.params.date
    if (!(date.match(/^[0-9]{4}-[0-9]{2}-[0-9]{2}$/))) {
        return res.status(404).json({
            "message": "Invalid date format"
        })
    }
    SensorData.find({
        time: {
            $gte: new Date(date),
            $lt: new Date(date + "T23:59:59.999Z")
        }
    }, (err, sensorDatas) => {
        if (err) {
            return next(err)
        }
        if (sensorDatas == null) {
            return res.status(404).json({
                "message": "SensorData not found for that date."
            })
        }
        res.json(sensorDatas)
    })
})


// Post sensorData
router.post('/api/sensorDatas', (req, res, next) => {
    var sensorData = new SensorData(req.body)
    // Check if the request body contains the a device id 
    if (!(req.body.device)) {
        return res.status(400).json({
            "message": "Device id is required"
        })
    }
    sensorData.save((err, sensorData) => {
        if (err) {
            return next(err)
        }
        res.json(sensorData)
    })
})

// Patch sensorData
router.patch('/api/sensorDatas/:id', (req, res, next) => {
    var id = req.params.id
    if (!(id.match(/^[0-9a-fA-F]{24}$/))) {
        return res.status(404).json({
            "message": "Item not found"
        })
    }
    SensorData.findByIdAndUpdate(id, req.body, (err, sensorData) => {
        if (err) {
            return next(err)
        }
        if (sensorData == null) {
            return res.status(404).json({
                "message": "SensorData not found."
            })
        }
        res.json(sensorData)
    })
})

// Delete sensorData
router.delete('/api/sensorDatas/:id', (req, res, next) => {
    var id = req.params.id
    if (!(id.match(/^[0-9a-fA-F]{24}$/))) {
        return res.status(404).json({
            "message": "Item not found"
        })
    }
    SensorData.findByIdAndRemove(id, (err, sensorData) => {
        if (err) {
            return next(err)
        }
        if (sensorData == null) {
            return res.status(404).json({
                "message": "SensorData not found."
            })
        }
        res.json(sensorData)
    })
})

// delete all sensorDatas
router.delete('/api/sensorDatas', (req, res, next) => {
    SensorData.remove({}, (err, sensorData) => {
        if (err) {
            return next(err)
        }
        res.json(sensorData)
    })
})

module.exports = router;
