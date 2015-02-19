import math

def main():
	values = [int(round(func(x / 256.0) * 255)) for x in range(256)]
	
	values_hex = [hex(x) for x in values]
	
	print ",\n  ".join([", ".join(values_hex[i*16:(i + 1) * 16]) for i in range(16)])
	
def func(x):
	return (1 - math.cos(x * math.pi)) / 2
	
main()