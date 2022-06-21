var express = require('express')
var router = express.Router()
var Device = require('../models/device')

// get all devices
router.get('/api/devices', (req, res, next) => {
    Device.find((err, Device) => {
        if (err) {
            return next(err)
        }
        res.json({
            "devices": Device
        })
    })
})

//get one device
router.get('/api/devices/:id', (req, res, next) => {
    var id = req.params.id
    if (!(id.match(/^[0-9a-fA-F]{24}$/))) {
        return res.status(404).json({
            "message": "Item not found"
        })
    }
    Device.findById(id, (err, device) => {
        if (err) {
            return next(err)
        }
        if (device == null) {
            return res.status(404).json({
                "message": "Device not found."
            })
        }
        res.json(device)
    })
})

// Post device
router.post('/api/devices', (req, res, next) => {
    var device = new Device(req.body)
    device.save((err, device) => {
        if (err) {
            return next(err)
        }
        res.json(device)
    })
})

// Patch device
router.patch('/api/devices/:id', (req, res, next) => {
    var id = req.params.id
    if (!(id.match(/^[0-9a-fA-F]{24}$/))) {
        return res.status(404).json({
            "message": "Item not found"
        })
    }
    Device.findByIdAndUpdate(id, req.body, (err, device) => {
        if (err) {
            return next(err)
        }
        if (device == null) {
            return res.status(404).json({
                "message": "Device not found."
            })
        }
        res.json(device)
    })
})

// Delete device
router.delete('/api/devices/:id', (req, res, next) => {
    var id = req.params.id
    if (!(id.match(/^[0-9a-fA-F]{24}$/))) {
        return res.status(404).json({
            "message": "Item not found"
        })
    }
    Device.findByIdAndRemove(id, (err, device) => {
        if (err) {
            return next(err)
        }
        if (device == null) {
            return res.status(404).json({
                "message": "Device not found."
            })
        }
        res.json(device)
    })
})

// Delete all devices
router.delete('/api/devices', (req, res, next) => {
    Device.remove((err, device) => {
        if (err) {
            return next(err)
        }
        res.json(device)
    })
})


module.exports = router;