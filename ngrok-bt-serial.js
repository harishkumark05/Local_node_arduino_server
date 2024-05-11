require('dotenv').config();

const express = require('express');
const app = express();
const cors = require('cors');
const http = require('http');
const amqp = require('amqplib');
// const rabbitmqUrl = process.env.RABBITMQ_URL;
const rabbitmqUrl ='amqps://hhhffwzt:18OB0sANoveOVY_QhztgUaXONis5qq_o@octopus.rmq3.cloudamqp.com/hhhffwzt';


const server = http.createServer(app);
// Enable CORS for all routes

// app.use(cors({
//     origin: "http://localhost:4200",.
//     methods: ["GET", "POST"],
//     allowedHeaders: ["Content-Type"]
// }));


app.use(cors());
app.use(express.json({ limit: '50mb' }));
app.use(express.urlencoded({ extended: true, limit: '50mb' }));

const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');

let tempData;

const settings = {
    path: 'COM6',
    baudRate: 9600
};
const connect = async (message) => {
    try {
        const connection = await amqp.connect(rabbitmqUrl);
        const channel = await connection.createChannel();
        const queueName = 'queue_A';

        await channel.assertQueue(queueName, { durable: false });

        console.log("Connected to RabbitMQ -A");
        channel.sendToQueue(queueName, Buffer.from(JSON.stringify(message)));
        
        // Close the channel and connection after sending the message
        await channel.close();
        await connection.close();
    } catch (error) {
        console.error('Error connecting to RabbitMQ:', error.message);
        // Retry connecting or implement other error handling logic as needed
    }
}

// Timer to call connect(tempData) every 5 minutes
setInterval(() => {
connect(tempData)
}, 0.5 * 60 * 1000); // 15 minutes in milliseconds

const port = new SerialPort({ path: settings.path, baudRate: settings.baudRate }, (err) => {
    if (err) {
        console.log('Error occurred');
    }
});

const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }));

port.write('main screen turn on', function (err) {
    if (err) {
        return console.log('Error on write: ', err.message);
    }
    console.log('message written');
});

// Wait for the first data from the serial port before emitting it to clients
parser.once('data', (firstData) => {
    console.log('First data from serial port:', firstData.toString());
    tempData = JSON.parse(firstData);
    connect(tempData)   
});

parser.on('data', (data) => {
//     // const sensorData = data.toString();
//         if(data){
//             const sensorData = JSON.parse(data);

//     console.log(sensorData);
//     tempData = sensorData;
//     // Broadcast the new data to all connected clients
//     connect(tempData)
// }else{
//     console.log('Error:no dara')
// }

 try {
        const sensorData = JSON.parse(data);
        console.log(sensorData);
        tempData = sensorData;
        
        // Check for smoke detection
        if (sensorData.value > 300) {
             connect(tempData)
        }

        // Check for motion detection
        if (sensorData.motion === 1) {
            connect(tempData)
        }
    } catch (error) {
        console.error('Error parsing sensor data:', error.message);
    }

});



const PORT = process.env.PORT || 3000;

server.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});
