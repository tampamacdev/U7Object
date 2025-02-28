#!/usr/bin/env node

const fs = require('fs');

// Function to filter options and return [filteredArgs, options]
function filterOptions(args) {
    const filteredArgs = [];
    const options = {};

    for (let i = 0; i < args.length; i++) {
        if (args[i].startsWith('--')) {
            const optionName = args[i].slice(2); // Remove '--' prefix
            if (i + 1 < args.length && !args[i + 1].startsWith('--')) {
                options[optionName] = args[i + 1];
                i++; // Skip the value
            } else {
                options[optionName] = '';
            }
        } else {
            filteredArgs.push(args[i]);
        }
    }

    return [filteredArgs, options];
}

// Parse command-line arguments
const args = process.argv.slice(2);
const [filteredArgs, options] = filterOptions(args);

// Validate arguments
const headerFile = filteredArgs.length === 1 ? filteredArgs[0] : null;
const prefix = options['prefix'] || null;

console.log('headerFile: ', headerFile, '|prefix: ', prefix);

if (!headerFile || !prefix) {
    console.error('Error: Both header file path and --prefix are required.');
    console.error('Usage: node c-header-to-html.js <path_to_header_file> --prefix <namespace_prefix>');
    console.error('Example: node c-header-to-html.js u7_api.h --prefix u7');
    process.exit(1);
}

// Read the C header file and split into lines
const headerContent = fs.readFileSync(headerFile, 'utf8');
const lines = headerContent.split('\n');

// Regex to match public methods with dynamic prefix
const methodRegex = new RegExp(`^([A-Za-z][A-Za-z0-9_* ]+)\\s+(${prefix}_[a-z_]+_[a-z_]+)\\s*\\(([^)]+)\\);$`);

// Extract methods
const methods = [];
for (const line of lines) {
    const match = methodRegex.exec(line);
    console.log('line: ', line);
    console.log('match: ', match);
    if (match !== null) {
        const returnType = match[1];
        const methodName = match[2];
        const params = match[3].split(',').map(p => p.trim());
        if (!methodName.includes('get_type') && !methodName.includes('construct')) {
            methods.push({ returnType, name: methodName, params });
        }
    }
}

// Generate HTML
let html = `<html><body><h1>${prefix.toUpperCase()} C API Documentation</h1><ul>`;
methods.forEach(method => {
    html += `<li><code>${method.returnType}</code> <strong>${method.name}</strong>(${method.params.join(', ')})</li>`;
});
html += '</ul></body></html>';

// Write to file
fs.writeFileSync('api_docs.html', html);