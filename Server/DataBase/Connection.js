const mongoose = require("mongoose")

const usuario = process.env.DB_USER
const senha = process.env.DB_PASS

const connect = ()=> {
    mongoose.connect(`mongodb+srv://${usuario}:${senha}@iot-rodrigo.qjmjnqv.mongodb.net/teste?retryWrites=true&w=majority`)
    const connection = mongoose.connection;

    connection.on("error",()=>{
        console.log("Erro ao conectar com o MongoDB.")
    })

    connection.on("open",()=>{
        console.log("Conectado com o MongoDb.")
    })
}

connect()