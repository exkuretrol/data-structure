all: uninstall install clean 

uninstall:
	@echo "Uninstalling package homework..."
	@python -m pip uninstall homework -y

install:
	@echo "Installing package homework..."
	@python setup.py install

clean:
	@echo "Cleaning up build files..."
	@rm -rf dist homework.egg-info include build
