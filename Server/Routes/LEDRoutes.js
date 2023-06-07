const router = require("express").Router();
const LedController = require("../Controllers/LedController");

router.get("/",LedController.ledState)
router.get("/state-led",LedController.ledState)

module.exports = router