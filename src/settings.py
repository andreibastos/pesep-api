# settings.py
from dotenv import load_dotenv
import os
load_dotenv(verbose=True)

# settings.py
SECRET_KEY = os.getenv('SECRET_KEY')
ROOT_DIR = os.getenv('ROOT_DIR')
SRC_DIR = ROOT_DIR + os.getenv('SRC_DIR')
HEADER_FILES = ROOT_DIR + os.getenv('HEADER_FILES')
PORT = os.environ.get('PORT', 5000)
DEBUG = os.environ.get('DEBUG', False) == 'True'
