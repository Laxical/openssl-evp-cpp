main:
	g++ cfiles/main.cpp cfiles/sha256.cpp cfiles/ecdsa.cpp cfiles/ecdsa_keygen.cpp -o object/main -lssl -lcrypto
	
exec:
	./object/main

clean:
	rm -rf ./object/main