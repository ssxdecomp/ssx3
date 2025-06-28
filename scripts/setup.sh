set -e

WINE_ROOT=~/.wine/drive_c
TOP=$(cd "$(dirname "$0")"; pwd)/..

download() {
	echo "Downloading $1..."
	wget -qP /tmp $1

	BASENAME=$(basename $1)

	#echo "moving files out of /tmp"
	#mv /tmp/$BASENAME $TOP
}

# download required files (registry + SDK package)
download "https://github.com/AngheloAlf/SN-Systems-ProDG_for_PS2_3.01/releases/latest/download/eegcc_2.95.3_sn_v1.36.tar.gz"

# apply environment variables from the registry file
# wine regedit prodg_env.reg

# Extract the compiler into the tools dir
mkdir $TOP/tools/cc/eegcc-2.95.3-V1.36
echo "Extracting compiler to $TOP/tools..."
tar -xzf /tmp/eegcc_2.95.3_sn_v1.36.tar.gz -C $TOP/tools/cc/eegcc-2.95.3-V1.36

echo "Removing temporary files..."
rm /tmp/eegcc_2.95.3_sn_v1.36.tar.gz"