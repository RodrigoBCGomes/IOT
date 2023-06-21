const Sensor = require("../Models/Sensor");

module.exports = class SensorController{
    static async sensorAtivado() {
        //Requisição é um pedido do ESP
        //Resposta é uma resposta da API
        const {nome, distancia} = req.body;
        const sensor = new Sensor({
            nome,distancia
        })
        try {
            await sensor.save();
            res.status(201).json({message: "Sensor salvo!",sensor: sensor})
        }   catch (error) {
            res.status(500).json({message: "Deu ruim!"})
        }
    }
}