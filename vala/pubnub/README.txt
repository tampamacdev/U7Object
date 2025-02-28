

export C_CORE_PATH="/PATH/TO/C_CORE/REPO"


./generate_pubnub_include.sh



gcc -o pubnub_client pubnub_client.c -I $C_CORE_PATH/include/pubnub -L $C_CORE_PATH/build -lpubnub -pthread