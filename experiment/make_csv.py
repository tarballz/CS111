# Try to generaet a csv file from a log
# You need to copy the log to the folder first

headers = 'inact\tactive'

log_file = open('debug.log')

table = [["Inactive", "Active", "Scanned Qs", "To Inactive", "To Cache", "Flush queued"]]

is_data = False
for line in log_file:
    line_data = line.split(':')[-1].strip()
    if is_data:
        table.append(line_data.split('\t'))
    is_data = headers in line_data

def naive_to_csv(table, fn):
    file = open(fn, 'w')
    for row in table:
        file.write(','.join(row) + '\n')
        
naive_to_csv(table, 'out.csv')
