class Reader(object):

    def __init__(self):
        self.pass_l = []
        self.inact_l = []
        self.active_l = []
        self.scanned_l = []
        self.toInact_l = []
        self.toCache_l = []
        self.flush_l = []

        self.avg_pass = 0.0
        self.avg_inact = 0.0
        self.avg_active = 0.0
        self.avg_scanned = 0.0
        self.avg_toInact = 0.0
        self.avg_toCache = 0.0
        self.avg_flush = 0.0

    def add_flush(self, num):
        self.flush_l.append(int(num))

    def add_toCache(self, num):
        self.toCache_l.append(int(num))

    def add_toInact(self, num):
        self.toInact_l.append(int(num))

    def add_scanned(self, num):
        self.scanned_l.append(int(num))

    def add_active(self, num):
        self.active_l.append(int(num))

    def add_inact(self, num):
        self.inact_l.append(int(num))

    def add_pass(self, num):
        self.pass_l.append(int(num))

    def take_avg(self):
        for e in self.pass_l:
            self.avg_pass += e
        self.avg_pass = self.avg_pass / len(self.pass_l)

        for e in self.inact_l:
            self.avg_inact += e
        self.avg_inact = self.avg_inact / len(self.inact_l)

        for e in self.active_l:
            self.avg_active += e
        self.avg_active = self.avg_active / len(self.active_l)

        for e in self.scanned_l:
            self.avg_scanned += e
        self.avg_scanned = self.avg_scanned / len(self.scanned_l)

        for e in self.toInact_l:
            self.avg_toInact += e
        self.avg_toInact = self.avg_toInact / len(self.toInact_l)

        for e in self.toCache_l:
            self.avg_toCache += e
        self.avg_toCache = self.avg_toCache / len(self.toCache_l)

        for e in self.flush_l:
            self.avg_flush += e
        self.avg_flush = self.avg_flush / len(self.flush_l)

    def print_avg(self):
        print "pass: " + str(self.avg_pass)
        print "inactive queue pages: " + str(self.avg_inact)
        print "active queue pages: " + str(self.avg_active)
        print "queues scanned: " + str(self.avg_scanned)
        print "pages moved to inactive: " + str(self.avg_toInact)
        print "pages moved to cache: " + str(self.avg_toCache)
        print "pages queued for flush: " + str(self.avg_flush)


    def print_l(self):
        for i in range(len(self.pass_l)):
            print str(self.pass_l[i]) + " " + str(self.inact_l[i]) + " " + str(self.active_l[i]) +  " " + \
                  str(self.scanned_l[i]) + " " + str(self.toInact_l[i]) + " " + str(self.toCache_l[i]) + \
                  " " + str(self.flush_l[i])
