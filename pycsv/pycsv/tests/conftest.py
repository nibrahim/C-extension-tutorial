def pytest_funcarg__setup(request):
    "Sets up the path and other things properly"
    import sys
    sys.path.append(".")
