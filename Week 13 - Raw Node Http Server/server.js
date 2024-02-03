const PORT = 3000;
const http = require('node:http')

const server = http.createServer((req, res) => {
    // send http headers
    res.writeHead(200, { 'Content-Type': 'text/plain' });
    // send body data
    res.write('hello world'); // 11 bytes
    // terminate response
    res.end();
});

// listen on port
server.listen(PORT, () => { console.log(`Listening on port ${PORT}`) });
