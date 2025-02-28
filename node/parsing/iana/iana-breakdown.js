#!/usr/bin/env node

const fs = require('fs');
const path = require('path');

// Check for input JSON file argument
if (process.argv.length < 3) {
    console.error('Usage: node generate-iana-site.js <path-to-ports.json>');
    process.exit(1);
}

const inputFile = process.argv[2];
const outputDir = 'iana_breakdown';

// Define port ranges (0-65535, in buckets)
const ranges = [];
for (let start = 0; start < 65536; start += 1000) {
    const end = Math.min(start + 999, 65535);
    ranges.push({ start, end });
}

// Read the JSON file
let ports;
try {
    const jsonData = fs.readFileSync(inputFile, 'utf8');
    ports = JSON.parse(jsonData);  // e.g., {"6379": "redis", "27017": "mongodb"}
} catch (err) {
    console.error('Error reading or parsing JSON:', err.message);
    process.exit(1);
}

// Create output directory
if (!fs.existsSync(outputDir)) {
    fs.mkdirSync(outputDir);
}

// Count ports in each range and prepare index content
const indexContent = ['<!DOCTYPE html>', '<html>', '<head>', '<title>IANA Port Breakdown</title>', '</head>', '<body>', '<a href="../selecting_static_port_number.html">Guidelines for Selecting Static Port Numbers in Custom Network Services</a>', '<h1>IANA Registered Port Ranges</h1>'];
const portKeys = Object.keys(ports).map(Number);  // Convert string keys to numbers

ranges.forEach(range => {
    const rangePorts = portKeys.filter(port => port >= range.start && port <= range.end);
    const count = rangePorts.length;
    const fileName = `${range.start}-${range.end}.html`;
    const linkText = range.start === 0 ? `${range.start}-${range.end} reserved` : `${range.start}-${range.end} (count ${count})`;

    // Generate subpage if there are ports in this range
    if (count > 0) {
        indexContent.push(`<a href="./${fileName}">${linkText}</a><br>`);

        const subpageContent = [
            '<!DOCTYPE html>', '<html>', '<head>', `<title>Ports ${range.start}-${range.end}</title>`, '</head>', '<body>',
            '<nav><a href="./index.html">Back</a></nav>',
            `<h1>IANA registered ports for range ${range.start}-${range.end}</h1>`, '<br>'
        ];
        rangePorts.sort((a, b) => a - b).forEach(port => {
            subpageContent.push(`${port} ${ports[port]}<br>`);
        });
        subpageContent.push('</body>', '</html>');
        fs.writeFileSync(path.join(outputDir, fileName), subpageContent.join('\n'));
    }
});

// Finish and write index.html
indexContent.push('</body>', '</html>');
fs.writeFileSync(path.join(outputDir, 'index.html'), indexContent.join('\n'));

console.log(`Static website generated in ${outputDir}/`);