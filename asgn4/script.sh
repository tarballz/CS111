# Test program for ASGN 4
# Run this with script with sudo or as root

echo Testing ASGN 4
echo Be sure to run this command with sudo or as root!
echo --------------------------------------------------------

# Get the protecfile program
echo Build and copy protecfile program
make -C ./aes
cp ./aes/protectfile .
cc setkey.c -o setkey

# Make some files
echo Create test files
mkdir base
mkdir layer
echo encrypted > base/encrypted.txt
echo plain     > base/plain.txt
echo decrypted > base/decrypted.txt

# Encrypt encrypted file
echo protect encrypted, protect/unprotect decrypted
./setkey 1 1
./protectfile -e 1 1 ./base/encrypted.txt
./protectfile -e 1 1 ./base/decrypted.txt
./protectfile -d 1 1 ./base/decrypted.txt

# Attempt invalid commands, should raise error
echo Attempt invalid protects should raise error
./protectfile -e 1 1 ./base/encrypted.txt
./protectfile -d 1 1 ./base/decrpyted.txt
./protectfile -d 1 1 ./base/plain.txt

# Mount the cryptofs system
echo Mount crpytofs
mount -t cryptofs base layer

# Read some files
echo Reading encrpyted from base, should be encrpyted
cat base/encrypted.txt
echo

echo reading plain from base, should be plaintext
cat base/plain.txt

echo reading decrypted from base, should be plaintext
cat base/decrypted.txt

# Read some fimes through crpyotfs
echo Reading encrpyted from layer, should be plaintext
cat layer/encrypted.txt

echo reading plain from layer, should be plaintext
cat layer/plain.txt

echo reading decrypted from layer, should be plaintext
cat layer/decrypted.txt
