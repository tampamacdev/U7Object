#!/usr/bin/env node

const fs = require('fs');
const csv = require('csv-parse');
const filesize = require("filesize");


function getFileSize(filePath) {
    try {
      const stats = fs.statSync(filePath);
      return stats.size; // Size in bytes
    } catch (err) {
      console.error(`Error getting file size: ${err.message}`);
      throw err;
    }
}
  
// Check for input file argument
if (process.argv.length < 3) {
    console.error('Usage: node csv-to-port-dictionary.js <path-to-service-names-port-numbers.csv>');
    process.exit(1);
}

const inputFile = process.argv[2];
const outputDict = {};

const size = getFileSize(inputFile);

console.error(`input file: ${inputFile}`);
console.error(`File size: ${size} bytes`);

// Read and parse the CSV file
fs.createReadStream(inputFile)
    .pipe(csv.parse({ columns: true, trim: true }))
    .on('data', (row) => {
        // Extract port number and service name
        const port = row['Port Number'];
        const service = row['Service Name'];

        // Only include rows with a valid port and service name
        if (port && service && /^\d+$/.test(port)) {
            outputDict[port] = service;
        }
    })
    .on('end', () => {
        // Write the JSON output to stdout or a file
        const jsonOutput = JSON.stringify(outputDict, null, 2);
        console.error(`jsonOutput size: ${filesize.filesize(jsonOutput.length)}`);

        console.log(jsonOutput);
        // Optionally save to file: fs.writeFileSync('ports.json', jsonOutput);
    })
    .on('error', (err) => {
        console.error('Error processing CSV:', err.message);
        process.exit(1);
    });