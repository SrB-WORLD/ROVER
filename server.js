const express = require('express');
const bodyParser = require('body-parser');
const axios = require('axios');
const app = express();
const port = 3000;

const arduinoIp = '172.20.10.6'; // Replace with the Arduino IP address

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

// Serve the index.html file
app.get('/', (req, res) => {
    res.sendFile(__dirname + '/index.html');
});


app.get('/forward',  async (req, res) => {
  try {
    // Example of fetching data from Arduino
    const response = await axios.get(`http://${arduinoIp}/forward`);
    res.send(`Polarity: ${response.data}`);
} catch (error) {
    console.error('Error fetching polarity', error);
    res.status(500).send('Error fetching polarity');
}
});

// Endpoint to fetch polarity from Arduino
app.get('/fetchPolarity', async (req, res) => {
    try {
        // Example of fetching data from Arduino
        const response = await axios.get(`http://${arduinoIp}/fetchPolarity`);
        res.send(`${response.data}`);
    } catch (error) {
        console.error('Error fetching polarity', error);
        res.status(500).send('Error fetching polarity');
    }
});

app.get('/fetchIR', async (req, res) => {
    try {
        // Example of fetching data from Arduino
        const response = await axios.get(`http://${arduinoIp}/fetchIR`);
        res.send(`${response.data}`);
    } catch (error) {
        console.error('Error fetching IR', error);
        res.status(500).send('Error fetching IR');
    }
});

app.get('/fetchRadio', async (req, res) => {
    try {
        // Example of fetching data from Arduino
        const response = await axios.get(`http://${arduinoIp}/fetchRadio`);
        res.send(`${response.data}`);
    } catch (error) {
        console.error('Error fetching Radio', error);
        res.status(500).send('Error fetching Radio');
    }
});

app.get('/fetchName', async (req, res) => {
    try {
        // Example of fetching data from Arduino
        const response = await axios.get(`http://${arduinoIp}/fetchName`);
        res.send(`${response.data}`);
    } catch (error) {
        console.error('Error fetching Name', error);
        res.status(500).send('Error fetching Name');
    }
});

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}/`);
});
