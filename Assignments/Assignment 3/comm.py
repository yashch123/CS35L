#!/usr/bin/python 

import random,sys,locale,string
from optparse import OptionParser 


def main() : 
  version_msg="%prog 2.0" 
  usage_msg="""%prog [-u123]...Compare 2 sorted files FILE1 and FILE2"""

  parser=OptionParser(version=version_msg,usage=usage_msg)
  
  parser.add_option("-1",action="store_true",dest="suppress1",default=0,help="suppress column 1: lines unique to first file")
  parser.add_option("-2",action="store_true",dest="suppress2",default=0,help="suppress column 2: lines unique to second file")
  parser.add_option("-3",action="store_true",dest="suppress3",default=0,help="suppress column 3: lines common to both files")
  parser.add_option("-u",action="store_true",dest="unsorted",default=0,help="sort if files are unsorted")
  
  options, args = parser.parse_args(sys.argv[1:]) 
  
  
  if len(args)!=2:
    parser.error("Incorrect number of operands")
    
  file1=args[0]
  file2=args[1]
  list1=[] #change
  list2=[] #change
  common=[]
  combine=[]
  
  if file1=="-" and file2=="-":
    parser.error("Both files cannot be standard input") #------------>CHECK THIS 
    
#if file1 is standard input
  if file1=="-":
    list1=sys.stdin.read().splitlines()
  else:
    try:
      f=open(file1,'r')
      list1=f.read().splitlines()
      f.close()
    except:
      parser.error("Invalid")
      
  if file2=="-":
    list2=sys.stdin.read().splitlines()
  else:
    try:
      f1=open(file2,'r')
      list2=f1.read().splitlines()
      f1.close()
    except:
      parser.error("Invalid")

#IF FILES ARE SORTED
  if options.unsorted==0:
              
              #Getting all common elements in common array
    for i in list1:
      if i in list2:
        common.append(i)        
 #Removing common elements from list1
    for x in common:
      if x in list1:
        list1.remove(x)

 #Removing common elements from list2
    for x in common:
      if x in list2:
        list2.remove(x)

 #All the cases
    combine=list1+common+list2
    combine.sort()

    if options.suppress1==0 and options.suppress2==0 and options.suppress3==0:
      for i in combine:
        if i in list1:
          sys.stdout.write(i+"\n")
        if i in list2:
          sys.stdout.write("\t"+i+"\n")
        if i in common:
          sys.stdout.write("\t\t"+i+"\n")
    elif options.suppress3==1 and options.suppress2==1 and options.suppress1==1:  #What to do here????????????
      exit

    elif options.suppress1==1 and options.suppress3==1:
      for i in list2:
        sys.stdout.write(i+"\n")

    elif options.suppress2==1 and options.suppress3==1:
      for i in list1:
        sys.stdout.write(i+"\n")
                     
    elif options.suppress1==1 and options.suppress2==1:
      for i in common:
        sys.stdout.write(i+"\n")

    elif options.suppress1==1:
      for i in combine: 
        if i in list2:
          sys.stdout.write(i+"\n")
        if i in common:
          sys.stdout.write("\t"+i+"\n")

    elif options.suppress2==1:
      for i in combine:
        if i in list1:
          sys.stdout.write(i+"\n")
        if i in common:
          sys.stdout.write("\t"+i+"\n")
                    
    elif options.suppress3==1:
      for i in combine:
        if i in list1:
          sys.stdout.write(i+"\n")
        if i in list2:
          sys.stdout.write("\t"+i+"\n")

#Unsorted:
#We make a new list from list2 in which all the common ones are deleted. Then we take list1 and this new list, add them and sort them. 

  if options.unsorted==1:
    count=0
#Remove all common elements from list2

    for i in list1:
      if  i in list2:
        common.append(i)

    for i in list2:
      if i in common:
        list2.remove(i)
    
#Not adding common in because list1 already contains the common elements
    combine=list1+list2
  
    if options.suppress1==0 and options.suppress2==0 and options.suppress3==0:
      for i in combine:
        if i in common:
          sys.stdout.write("\t\t"+i+"\n")
        elif i in list1:
          sys.stdout.write(i+"\n")
        elif i in list2:
          sys.stdout.write("\t"+i+"\n")

    elif options.suppress3==1 and options.suppress2==1 and options.suppress1==1: 
      exit

    elif options.suppress1==1 and options.suppress3==1:
      for i in list2:
        sys.stdout.write(i+"\n")

    elif options.suppress2==1 and options.suppress3==1:
      for i in list1:
        if not i in common:
          sys.stdout.write(i+"\n")
   
    elif options.suppress1==1 and options.suppress2==1:
      for i in common:
        sys.stdout.write(i+"\n")

    elif options.suppress1==1:
      for i in combine:
        if i in common:
          sys.stdout.write("\t"+i+"\n")
        if i in list2:
          sys.stdout.write(i+"\n")
 
    elif options.suppress2==1:
      for i in combine:
        if i in common:
          sys.stdout.write("\t"+i+"\n")
        elif i in list1:
          sys.stdout.write(i+"\n")

    elif options.suppress3==1:
      for i in combine:
        if i in common:
          continue
        if i in list1:
          sys.stdout.write(i+"\n")
        if i in list2:
          sys.stdout.write("\t"+i+"\n")
    
if __name__ == "__main__":
  main()
