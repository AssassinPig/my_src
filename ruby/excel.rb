require 'win32ole'

excel = WIN32OLE.new("excel.application")
excel.Visible = true
workbook = excel.WorkBooks.Open("d:\\test.xlsx")
worksheet = excel.WorkSheets("Sheet1").Activate

worksheet = workbook.Worksheets(1)
worksheet.Select

print worksheet.Range('c2').value
print "\n"

excel.ActiveWorkbook.Close(1)
excel.Quit()
