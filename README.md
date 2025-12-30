Bank Statement Expense Calculator

A command-line utility written in C to calculate monthly expenses from password-protected credit card PDF statements.

The tool converts PDF statements into text, parses transaction data, and computes total monthly debit (DR) expenses.

✨ Features

Supports password-protected PDFs CLI-based (Linux-friendly) Month & year based expense filtering Handles masked card statements Safe parsing using sscanf Designed for HDFC credit card statements

🛠️ Dependencies

GCC
pdftotext (from poppler-utils)

Install on Ubuntu:
sudo apt install poppler-utils

Build:
gcc -Wall -Wextra calculator.c -o calculator

./calculator -b HDFC -p PASSWORD -m Feb -y 2025 -n statement.pdf

Option	Description
-b	Bank name (e.g. HDFC)
-p	PDF password
-m	Month (Jan, Feb, Mar…)
-y	Year (2024, 2025…)
-n	PDF statement file

Output:
Total Expense of Month Feb is 21510.79

⚠️ Limitations

Password is passed via CLI (visible via ps)
Statement format is bank-specific (HDFC)
Uses external tool (pdftotext)

🧠 Future Enhancements

Secure password input (no echo)
Support for multiple banks
Card-wise filtering
CSV export
Avoid system() using fork/exec

👨‍💻 Author

Jithendra P I
Embedded Software Developer