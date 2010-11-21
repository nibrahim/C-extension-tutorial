def test_import(setup):
    "Try importing the module"
    import pycsv


def test_csvfile(setup):
    "Initialise a CSVFile object with a file and check the file "
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
            
    

