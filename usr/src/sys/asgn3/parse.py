iteration = 1

pass_l = []
inact_l = []
active_l = []
scanned_l = []
toInact_l = []
toCache_l = []
flush_l = []

m = [pass_l, inact_l, active_l, scanned_l, toInact_l, toCache_l,flush_l] 


for i in range(iteration):
	# print "{}_debug.log".format(i)
	f = open("{}_debug.log".format(i), 'r')
	lines_list = f.read()
	lines_list = lines_list.split("\n")
	for entry in lines_list:
		line = entry.split(" ")
		try:
			flush_l.append(int(line[len(line) - 1]))
			toCache_l.append(int(line[len(line) - 2]))
			toInact_l.append(int(line[len(line) - 3]))
			scanned_l.append(int(line[len(line) - 4]))
			active_l.append(int(line[len(line) - 5]))
			inact_l.append(int(line[len(line) - 6]))
			pass_l.append(int(line[len(line) - 7]))
		except ValueError:
			print "Invalid char"
for i in range(len(pass_l)):
	print str(pass_l[i]) + " " + str(inact_l[i]) + " " + str(active_l[i]) +  " " + \
	      str(scanned_l[i]) + " " + str(toInact_l[i]) + " " + str(toCache_l[i]) + \
	      " " + str(flush_l[i])


def is_number(s):
	try:
		int(s)
		return True
	except ValueError:
		return False