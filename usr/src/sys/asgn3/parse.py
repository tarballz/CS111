from Reader import Reader

# pass_l = []
# inact_l = []
# active_l = []
# scanned_l = []
# toInact_l = []
# toCache_l = []
# flush_l = []

# m = [pass_l, inact_l, active_l, scanned_l, toInact_l, toCache_l,flush_l] 


inact_p = Reader()
activ_p = Reader()


iteration = 1
for i in range(iteration):
	# print "{}_debug.log".format(i)
	f = open("{}_debug.log".format(i), 'r')
	lines_list = f.read()
	lines_list = lines_list.split("\n")
	count = 0
	for entry in lines_list:
		line = entry.split(" ")
		try:
			# Inactive pass
			if count % 2 == 0:
				inact_p.add_flush(line[len(line) - 1])
				inact_p.add_toCache(line[len(line) - 2])
				inact_p.add_toInact(line[len(line) - 3])
				inact_p.add_scanned(line[len(line) - 4])
				inact_p.add_active(line[len(line) - 5])
				inact_p.add_inact(line[len(line) - 6])
				inact_p.add_pass(line[len(line) - 7])
			# Active pass
			else:
				activ_p.add_flush(line[len(line) - 1])
				activ_p.add_toCache(line[len(line) - 2])
				activ_p.add_toInact(line[len(line) - 3])
				activ_p.add_scanned(line[len(line) - 4])
				activ_p.add_active(line[len(line) - 5])
				activ_p.add_inact(line[len(line) - 6])
				activ_p.add_pass(line[len(line) - 7])
		except ValueError:
			print ''
		count += 1

# inact_p.print_l()
print "INACTIVE PASS:"
inact_p.take_avg()
inact_p.print_avg()

print "\nACTIVE PASS:"
activ_p.take_avg()
activ_p.print_avg()


# for i in range(len(pass_l)):
# 	print str(pass_l[i]) + " " + str(inact_l[i]) + " " + str(active_l[i]) +  " " + \
# 	      str(scanned_l[i]) + " " + str(toInact_l[i]) + " " + str(toCache_l[i]) + \
# 	      " " + str(flush_l[i])
