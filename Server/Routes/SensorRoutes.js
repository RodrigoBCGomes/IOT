const router = require("express").Router()
const SensorController = require("../Controllers/SensorController")

router.post("/ativado",sensorController.sensorAtivado)

router.post("/ativado")