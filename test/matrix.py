


size = input("Matrix size?\n")


bytes = size * size * 4

kbytes = bytes /1024.0
mbytes = kbytes/1024.0
gbytes = mbytes/1024.0


print "B:", bytes
print "KB:", kbytes
print "MB:", mbytes
print "GB:", gbytes