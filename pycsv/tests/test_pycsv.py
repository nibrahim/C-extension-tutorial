def test_import(setup):
    "Try importing the module"
    import pycsv


def test_csvfile(setup):
    "Initialise a CSVFile object with a file and check the file "
    import pycsv
    with open("tests/sample.csv") as f:
        csvfile = pycsv.CSVFile(f)
    

