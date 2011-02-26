def test_import(setup):
    "Try importing the module"
    import pycsv


def test_csvfile(setup):
    "Initialise a CSVFile object with a file"
    import pycsv
    with open("tests/sample.csv") as f:
        csvfile = pycsv.CSVFile(f)


def test_csvfile_typeerror(setup):
    "Try initilialising CSVFile without arguments. Should raise TypeError"
    import pycsv
    try:
        csvfile = pycsv.CSVFile()
        assert False, "Didn't raise TypeError when CSVFile instantiated without args"
    except TypeError:
        return
            
def test_csvfile_storing_file(setup):
    "Makes sure that the provided file like object is stored in the CSVFile for later use"
    import pycsv
    with open("tests/sample.csv") as f:
        csvfile = pycsv.CSVFile(f)
        assert csvfile._file == f, "Stored _file is not the one we created"
        
def test_csvfile_parse_method(setup):
    "Checks to see if there is a parse method that can be called"
    import pycsv

    with open("tests/sample.csv") as f:
        csvfile = pycsv.CSVFile(f)
        csvfile.parse()
        assert csvfile.parse.__doc__ == "Parses the actual CSV File"

def test_csvfile_cell_callback(setup):
    "Checks to see if the callback method for each cell and each row is called"
    import pycsv

    # A simple "struct" (from http://stackoverflow.com/questions/1878710/struct-objects-in-python/1878803#1878803)
    tmp = lambda : 0
    tmp.crow = []
    tmp.rows = []

    def row_callback(data):
        data.rows.append(data.crow)
        data.crow = []
        
    def cell_callback(cell, data):
        data.crow.append(cell)

    with open("tests/sample.csv") as f:
        csvfile = pycsv.CSVFile(f)
        csvfile.parse(cell_callback, row_callback, tmp)
        assert tmp.rows == [["Header0", "Header1", "Header2"], ["Data00", "Data01", "Data02"], ["Data10", "Data11", "Data12"]]

