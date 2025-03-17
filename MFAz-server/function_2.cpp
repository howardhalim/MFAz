#include "function.h"
#ifdef MR_CPP
#include "miracl.h"
#else
extern "C" {
#include "miracl.h"
}
#endif

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>

#include "bloom.h"
#include "bloom_func.h"
#include <curl/curl.h>
#include "api.h"


using namespace std;

struct bloom bloom;
#define QBITS 384
#if QBITS == 384
char Q[] = "16116817824962109488866668900920636677531584920802547220618262286315850221220703686033374354676380343499169226770823";
char P[] = "155778577698976036390276104853506277431396443846648619394910963450433688495988465867615149104352026393834314866528460274579587347293431426152219907726386639970745760451103047528344354553635990082404934583866180828511227573805016338141930999323387994540996283497583527923100118228818052852994539999031623776551";
char U[] = "9665591520039550400103650368027629327116932607627880365399505899831563100650536370603523292695054609099147813148740684094597813746342623514179220683907565540198448153448510491166549256147799850";
char G[] = "138433720961437072823522515036372062314985386579187376506863294585874198991284954161435707330787869305924839974549686904631810805341144091808884252204197008429557966740454365283958641981562438331666318275100029304950863876578718476814360597358719064830016300216307892955738749196446967880482207086456063809489";
#elif QBITS == 192
char Q[] = "6021530268201170981406072123875118437937552816969109798559";
char P[] = "98471104283046609139765310843874470871738024290660464868073138389797461616406362238418313076082471976305110973454179841342539071818225003379310918384510627054922941626128315343728769366070520401165640601367078065187788633315734145421293101407742349153949998204459726066981378182918320708914802132513027555911";
char U[] = "16353169360130637478427787917917682863444549312336545027218277405929566940354673130927302142430291569683141648715111460038969406790232484964745135937533589209408891882653720646658469272179712943953713646974695747266241688193822065640055786485195818490";
char G[] = "92094294054001703385617797402711775851451189037171663934225115449351602418696955336834534170299587671866376501403423596268155023749837966799257816586736626840808285851812435140714852378486227208211368247948031159711406023970896043424295911314843416619859325171923905132204239206944851199462372470352374759215";
#elif QBITS == 128
char Q[] = "94693613170104697533803587959663296711";
char P[] = "90311009993780571931748769611003671208556541996983188127697170777097781146177072701209845657290380912942162336767388311842835892517095417278511588810484469374172427435667025108951276799152548413072406896161681388927275095670219761885290248201907465206413102719692354133707440163867563749976250267108515425161";
char U[] = "953718069998539902602768165252754366203679264924624823769016812493790448534605948515691163453058991442701595058533946066500336134920395771533956411250386579878549008815575117905529513448854007780248816141600016990522060976537051010520916858642710625784786874645525397560";
char G[] = "14714281610273474822693655249839029221833675918397973660269051289134100010588011231416738027722665030962034665062699953032658217371662283623404343080842459667854170364215468467882575796557534699645013527666807212974068746956708243977462351848161030911720140912910359421487121488338727273645614626290965297428";
#endif

int bloom_entries = 1000;
float false_positive_rate = 0.01;


char *concatenateData(int Ui, const vector<string> &Oi, const vector<string> &Ri, const char *Ts)
{
    std::string op_list="";
    for (int i = 0; i < Oi.size();i++){
        op_list += Oi[i];
    }

    std::string resc_list = "";
    for (int i = 0; i < Ri.size();i++){
        resc_list += Ri[i];
    }

    char* res = new char[500];
    snprintf(res, 500, "%d%s%s%s", Ui, op_list.c_str(), resc_list.c_str(), Ts);
    return res;
}

string generateVerificationPoint(const char *GAij, const char *Si){
    char vp[1000];
    snprintf(vp, sizeof(vp), "%s%s", GAij, Si);
    char VPij[1000];
    hashing(vp, strlen(vp), VPij);

    return VPij;
}

string addition(string num1, string num2){
    miracl *mip = mirsys(65535, 10);
    big res = mirvar(0);
    big n1 = mirvar(0);
    big n2 = mirvar(0);
    
    int nm1 = stoi(num1);
    int nm2 = stoi(num2);

    convert(nm1,n1);
    convert(nm2,n2);


    add(n1,n2,res);

    

    char ret[1000];
    cotstr(res,ret);

    
    return ret;
}

char *hashing(char *str, int strlength, char* hash){ /* compute hash function */
    static char h[32];
    int ch;
    sha sh;
    shs256_init(&sh);
    for (int i = 0; i < strlength; i++)
    {
        ch = str[i];
        shs256_process(&sh, ch);
    }

    shs256_hash(&sh, h);
    big ha = mirvar(0);
    bytes_to_big(32, h, ha);
    cotstr(ha,hash);
    
    return h;
}

string session_id_generator(int id){

    //start use MIRACL
    miracl *mip = mirsys(65535, 10);
    time_t t = time(NULL);
    char Ts[20];
    snprintf(Ts, sizeof(Ts), "%ld", t);
    
    stringstream ss;
    ss << Ts << id;
    string combined_seed = ss.str();
    char combined[300];
    strncpy(combined,combined_seed.c_str(), sizeof(combined));

    cout<<combined<<endl;

    big seed = mirvar(0);
    cinstr (seed,combined);
    
   
    
    // Initialize random seed for MIRACL
    irand(time(0));  // Optionally use the current time to further randomize

    // Generate a random big number q using the bigrand function
    big q = mirvar(0);
    bigrand(seed, q);  // Using the seed as input to the bigrand function

    // Now add q and the user ID (id as a big number)
    big userid_big = mirvar(id);  
    big temp = mirvar(0);
    add(userid_big, q, temp);  

    big g = mirvar(0);  
    big p = mirvar(0);  

    cinstr(g,G);
    cinstr(p,P);
    big result = mirvar(0);
    powmod(g, temp, p, result);  // result = g^temp mod p

    // Convert the result big number to a string to return
    char result_str[500];  // Adjust size as needed
    cotstr(result, result_str);  // Convert result big integer to string
    char res[500];
    hashing(result_str, strlen(result_str), res);
    return string(res);
    // return "12345";
}


bool checkVerificationPoint(struct bloom * bloom, string check_vp){
    char check_vps[1000];
    strcpy(check_vps, check_vp.c_str());
    int check_len = strlen(check_vps);
    bool granted = false;
    if (bloom_check(bloom, &check_vps, check_len))
    {
        granted = true;
        printf("\n\nIt may be there!\n");
    }
    else
    {
        printf("\n\nIts not there!\n");
    }

    return granted;
}

void addVerificationPoint(struct bloom * bloom, string VPij){
    char vps[1000];
    strcpy(vps,VPij.c_str());
    int len = strlen(vps);

    bloom_add(bloom, &vps, len);
}
string convert_to_hexadecimal(unsigned char *bit_array, size_t size)
{
    string hex_string;
    char buffer[3]; // Buffer to hold two hex digits and a null terminator

    for (size_t i = 0; i < size; ++i)
    {
        snprintf(buffer, sizeof(buffer), "%02x", bit_array[i]);
        hex_string += buffer;
    }

    return hex_string;
}

void convert_from_hexadecimal(struct bloom *bloom, string &hex_string)
{
    for (size_t i = 0; i < hex_string.length(); i+=2){
        char buffer[3];
        snprintf(buffer, sizeof(buffer), "%c%c", hex_string[i], hex_string[i+1]);

        int temp = stoi(buffer, nullptr, 16);
        bloom->bf[i / 2] = temp;
    }
}

char *userRequest(int Ui, const vector<string> &Oi, const vector<string> &Ri, const char *SGAi)
{

    //return value
    char *result = new char[1000];

    //start use MIRACL
    miracl *mip = mirsys(65535, 10);

    // get current Timestamp in UNIX format
    time_t t = time(NULL);
    char Ts[20];
    snprintf(Ts, sizeof(Ts), "%ld", t);

    std::cout << "Server Timestamp: " << Ts << endl;

    //read user secret seed
    // big secret_seed = read_secret(Ui);
    big secret_seed = mirvar(1234);
    char Si[1000];
    cotstr(secret_seed, Si);

    //init bloom
    bloom_init(&bloom, bloom_entries, false_positive_rate);

    // retrive the latest bloom filter
    std::string latest_bloom = getRequest();

    // convert bloom from hexadecimal (API) to unsigned char and assign to bloom->bf
    convert_from_hexadecimal(&bloom, latest_bloom);

    big ga_temp = mirvar(1);
    
    // char ga_history[300];
    // cotstr(ga_temp, ga_history);

    //compute VPs History to Check
    string check_vp = generateVerificationPoint(SGAi, "1234");

    cout<<check_vp<<endl;
    cout<<"-------------"<<endl;

    if(!checkVerificationPoint(&bloom, check_vp)){
        snprintf(result, 100, "Access Denied");
        return result;
    }

    // Concatenate data
    char* data = new char[500];
    snprintf(data, 500, "%s", concatenateData(Ui, Oi, Ri, Ts));

    // big res;
    // res = mirvar(1);
    char res[1000];
    hashing(data, strlen(data), res);

    char GAij[300];
    // cotnum(res, stdout);

    strcpy(GAij, res);

    string VPij = generateVerificationPoint(GAij, Si);

    //save new verificationpoint
    // char verif_file_path[256];
    // sprintf(verif_file_path, "verification_point/verification_point_%d_%s.txt", Ui, Ts);
    // FILE *verif_file = fopen(verif_file_path, "w");
    // cotnum(VPij, verif_file);

    addVerificationPoint(&bloom, VPij);

    //sent it to blockchain
    std::string params = (convert_to_hexadecimal(bloom.bf, bloom.bytes));
    postRequest(params);

    snprintf(result, 1000, "%s", GAij);
    return result;
}

char *authUserRequest(int Ui, const vector<string> &Oi, const vector<string> &Ri)
{
    //return value
    char *result = new char[1000];

    //start use MIRACL
    miracl *mip = mirsys(65535, 10);

    // get current Timestamp in UNIX format
    time_t t = time(NULL);
    char Ts[20];
    snprintf(Ts, sizeof(Ts), "%ld", t);

    std::cout << "Server Timestamp: " << Ts<<"\n";

    //init bloom
    bloom_init(&bloom, bloom_entries, false_positive_rate);

    // retrive the latest bloom filter
    string latest_bloom = getRequest();

    // cout<<"Latest: "<<latest_bloom<<endl;

    // Concatenate data
    char* data = new char[500];
    snprintf(data, 500, "%s", concatenateData(Ui, Oi, Ri, Ts));

    // big res;
    // res = mirvar(1);
    char res[1000];
    hashing(data, strlen(data), res);

    char GAij[400];
    // cotnum(res, stdout);

    // cotstr(res, GAij);
    strcpy(GAij,res);

    string VPij = generateVerificationPoint(GAij, "1234");

    cout<<"VP: "<<VPij<<endl;

    addVerificationPoint(&bloom, VPij);

    //sent it to blockchain
    std::string params = (convert_to_hexadecimal(bloom.bf, bloom.bytes));
    postRequest(params);

    snprintf(result, 1000, "%s", GAij);
    return result;
}