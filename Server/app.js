const express = require("express");
const cors = require("cors");
const app = express();
const LedRouter = require("./Routes/LEDRoutes");
const SensorRoutes = require("./Routes/SensorRoutes")

require("dotenv").config()

app.use(cors());
app.use("/sensor",sensorroutes)
app.use("/led", LedRouter);

app.get("/",(req,res)=>{
    res.json({message: "Bem vindo à minha API, para o IOT"})
})
app.listen(3000,()=>{
    console.log("Servidor rodando na porta 3000, para acessar use http://localhost:3000")
})