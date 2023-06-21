const mongoose = require("mongoose")

const sensorSchema = new mongoose.Schema({
    nome: String,
    distancia: Number,
    horario: {type: Date,default: Date.now}
})

const Sensor = mongoose.model("Sensor",sensorSchema)