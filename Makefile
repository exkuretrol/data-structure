.PHONY: all uninstall install install_requirement clean run

all: uninstall install clean 

uninstall:
	@echo "Uninstalling package homework..."
	@python -m pip uninstall homework -y

install:
	@echo "Installing package homework..."
	@python setup.py install

install_requirement:
	@brew install graphviz
	@export CFLAGS=-I$(brew --prefix graphviz)/include/
	@export LDFLAGS=-L$(brew --prefix graphviz)/lib/
	@pip install pygrapviz
	@pip install -r requirements.txt

clean:
	@echo "Cleaning up build files..."
	@rm -rf dist homework.egg-info include build

run:
	@streamlit run app.py
