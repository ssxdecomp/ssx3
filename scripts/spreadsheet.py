import requests
import pandas as pd
import re

# --- CONFIGURATION ---
# Direct download URL to the Excel (.xlsx) file from Google Sheets
# Make sure to use the export link format like below:
# https://docs.google.com/spreadsheets/d/YOUR_SHEET_ID/export?format=xlsx&id=YOUR_SHEET_ID
sheet_xlsx_url = "https://docs.google.com/spreadsheets/d/1lS58dZvimPbrQ4VkwB_JSMD-bLl_StKPWKS2KQGa_Ak/export?format=xlsx&id=1lS58dZvimPbrQ4VkwB_JSMD-bLl_StKPWKS2KQGa_Ak"
input_txt_path = "config/symbol_addrs.txt"
marker_line = "// Spreadsheet Auto Generation"
output_format = "{name} = {addr}; //type:func"
address_offset = 0xFF000
temp_excel_file = "temp_sheet.xlsx"
target_sheet_name = "Found Functions"
addresses = []
seen_names = set()

# --- Step 1: Download the Excel Sheet ---
def download_sheet(xlsx_url):
    response = requests.get(xlsx_url)
    response.raise_for_status()
    with open(temp_excel_file, "wb") as f:
        f.write(response.content)

# --- Step 2: Clean the text file above the marker ---
def clean_text_file(path, marker):
    with open(path, "r") as f:
        lines = f.readlines()

    # Find marker line and keep everything before and including it
    for i, line in enumerate(lines):
        if marker in line:
            cleaned = lines[:i+1]
            break
        parts = line.split()
        if len(parts) >= 3 and parts[1] == '=' and parts[2].startswith("0x"):
            hex_addr = parts[2].rstrip(';')
            try:
                int_addr = int(hex_addr, 16)
                addresses.append(int_addr)
            except ValueError:
                continue  # Skip if not a valid hex 
    else:
        cleaned = lines  # if marker not found, keep entire file

    with open(path, "w") as f:
        f.writelines(cleaned)
        
        
def check_name(name, iteration):
    tempname = f"{name}{iteration}"
    if iteration == 0:
        tempname = name
    if tempname in seen_names:
        tempname = check_name(name, iteration+1)
        return tempname
    else:
        seen_names.add(tempname)
        return tempname

# --- Step 3–4: Process spreadsheet and alter addresses ---
def process_sheet_and_append(path):
    df = pd.read_excel(temp_excel_file, sheet_name=target_sheet_name)
    if 'Demangled Name' not in df.columns or 'PS2 Address' not in df.columns:
        raise ValueError("Required columns not found in the sheet.")

    with open(path, "a") as f:
        for _, row in df.iterrows():
            # Extract and clean name
            raw_name = str(row['Demangled Name']).strip()
            name = raw_name.split('(')[0].strip()  # Remove everything after '('
            name = name.replace('::', '_') 
            name = name.replace(' ', '_')
            name = name.replace('~', '_') 
            name = name.replace('[', '')
            name = name.replace(']', '')             
            
            addr = str(row['PS2 Address']).strip()
            
            name = check_name(name, 0)
            
            new_addr = int(addr, 16)# - address_offset
            
            if new_addr in addresses:
                name = "//" + name
            else:
                formatted_line = output_format.format(name=name, addr=f"0x{new_addr:08X}")
                f.write("\n" +formatted_line)
                print(formatted_line)

# --- MAIN ---
if __name__ == "__main__":
    download_sheet(sheet_xlsx_url)
    clean_text_file(input_txt_path, marker_line)
    process_sheet_and_append(input_txt_path)
    print("Done.")