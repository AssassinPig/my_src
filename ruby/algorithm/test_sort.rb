def bubble_sort(a)
  i=0
  while i<a.length
    j=a.length-1
    flag=a[i]
    while i<j
      if a[j]<a[i]
        flag=a[j]
        a[j]=a[i]
        a[i]=flag
      end
      j-=1
    end
    i+=1
  end
  return a
end

a=[3, 6, 7, 5, 8, 1, 0, 9, 4, 2]
print "befor #{a}\n"
print "bubble_sort #{bubble_sort(a)}\n"
