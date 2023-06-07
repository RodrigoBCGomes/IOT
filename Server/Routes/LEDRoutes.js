const router = require("express").Router();
const LedController = require("../Contrllers/LedController");

router.get("/",LedController.ledState)
router.get("/state-led",LedController.ledState)

module.exports = router