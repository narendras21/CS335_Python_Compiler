#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <map>
#include <vector>
#include <stack>
#include <utility>
#include<bits/stdc++.h>
using namespace std;

extern FILE *yyin;
extern int yylineno;
extern char* yytext;



///////////////////////////////////////////////////////////////////////
//start modifying
///////////////////////////////////////////////////////////////////////
string asm_file = "asm.s";
class quad{
    public:
    string op;
    string arg1;
    string arg2;
    string result;
    string code = "";        // Construct from each node
    string insType = "";     // instruction type
    int rel_jump = 0, abs_jump = 0, ins_line = 0;
    int made_from = 0;
    bool is_target = false;
    
    enum code_code {
        BINARY,
        UNARY,
        ASSIGNMENT,
        CONDITIONAL,
        CAST,
        STORE,
        LOAD,
        FUNC_CALL,
        GOTO,
        BEGIN_FUNC,
        END_FUNC,
        RETURN,
        SHIFT_POINTER,
        PUSH_PARAM,
        POP_PARAM,
        RETURN_VAL
    };

    quad();
    quad(string r, string a1, string o, string a2, string ins){
        this->result = r;
        this->arg1 = a1;
        this->op = o;
        this->arg2 = a2;
        this->insType = ins;
    };     // res = arg1 op arg2
    // void make_code();                                   // Recreate code
    // void make_code_from_binary();                       // r = a1 op a2;
    // void make_code_from_unary();                        // r = op a1;
    // void make_code_from_assignment();                   // r = a1;
    // void make_code_from_conditional();                  // IFTRUE/FALSE a1 GOTO [filled later using check_jump()];
    // void make_code_from_cast();                         // r = (a2) a1;
    // void make_code_from_store();                        // *(r) = a1;
    // void make_code_from_load();                         // r = *(a1);
    // void make_code_from_func_call();                    // callfunc a1;
    // void make_code_from_goto();                         // GOTO a1;
    // void make_code_begin_func();                        // begin_func x;
    // void make_code_end_func();                          // end_func;
    // void make_code_from_return();                       // return a1;
    // void make_code_shift_pointer();                     // shift stack pointer
    // void make_code_push_param();                        // pushparam a1;
    // void make_code_pop_param();                         // r = popparam;
    // void make_code_from_return_val();                   // r = return_value;
    // void check_jump(const int);
};

void construct_subroutine_table(vector<quad> subroutine_ins);

const int stack_offset = 8;
int func_count = 0;
map<string, string> func_name_map;

class instruction{
    public:

    string op = "";
    string arg1 = "";
    string arg2 = "";
    string arg3 = "";
    string code = "";
    string ins_type = "";

    string comment = "";

    // instruction(){}
    instruction(string op = "", string a1 = "", string a2 = "", string a3 = "", string it = "ins", string comment = ""):op(op), arg1(a1), arg2(a2), arg3(a3), ins_type(it), comment(comment){
        
        if(it == "ins") {           // default instructions
            // cout<<"Inside default instruction: op = "<<op<<", arg1= "<<a1<<", arg2= "<<a2<<endl;
            if(arg3 == "") {
                code = "\t\t" + op;
                if(arg1 != ""){
                    code += "\t" + arg1;
                } 
                if(arg2 != ""){
                    code += ",\t" + arg2;
                }
            }
            else {

            }
        }
        else if(it == "segment") {  // text segment, global segment
            code = op;
            if(a1 != "") {
                code += "\t" + a1;
            }
        }
        else if(it == "label") {    // jump labels and subroutine labels
            code = arg1 + ":";
        }
        else if(it == "comment") {
            code = "\n\t\t# " + comment;
            return;
        }
        else {                      // other instruction types if used

        }
        if(comment != ""){
            code += "\t\t# " + comment;
        }
        code += "\n";
    }
    // void gen_code();
};




vector<instruction> make_x86_code(quad, int x = 0, int y = 0, int z = 0);
vector< vector<quad> > subroutines;
vector<instruction> code;

bool isVariable(string s);

void gen_fixed_subroutines();
void gen_text();
void gen_global();
void get_tac_subroutines();
void print_code(string asm_file = "asm.s");

class subroutine_entry{
    public:

    string name = "";
    int offset = 0;         // offset from the base pointer in subroutine

    subroutine_entry(){}
    subroutine_entry(string name, int offset){
        this -> name = name;
        this -> offset = offset;
    }
    // other entries may be added later
};

class subroutine_table{
    public:

    string subroutine_name;
    int is_main_function = false;
    map<string, subroutine_entry> lookup_table;
    int total_space;
    int number_of_params = 0;

    subroutine_table(){}

    void construct_subroutine_table(vector<quad> subroutine_ins) {
        int pop_cnt = 2;         // 1 8 byte space for the return address + old base pointer
        int local_offset = 8;    // 8 callee saved registers hence, 8 spaces kept free, rsp shall automatically be restored, rbp too
        
        for(quad q : subroutine_ins) {
            if(q.insType == "begin_func" || q.insType == "shift_pointer" || q.insType == "func_call") {   // No nested procedures
                continue; 
            }
            
            if(q.insType == "pop_param") {
                this -> lookup_table[q.result] = subroutine_entry(q.result, stack_offset*pop_cnt);
                pop_cnt++;
            }
            else {
                if(q.insType == "conditional") {
                    if(this -> lookup_table.find(q.arg1) == this -> lookup_table.end() && isVariable(q.arg1)) {
                        this -> lookup_table[q.arg1] = subroutine_entry(q.arg1, -stack_offset*local_offset);
                        local_offset++;
                    }
                }
                else if(q.insType == "goto"){
                    continue;
                }
                else {
                    if(q.arg1 != "" && this -> lookup_table.find(q.arg1) == this -> lookup_table.end() && isVariable(q.arg1)) {
                        this -> lookup_table[q.arg1] = subroutine_entry(q.arg1, -stack_offset*local_offset);
                        local_offset++;
                    }
                    else if(q.arg2 != "" && this -> lookup_table.find(q.arg2) == this -> lookup_table.end() && isVariable(q.arg2)) {
                        this -> lookup_table[q.arg2] = subroutine_entry(q.arg2, -stack_offset*local_offset);
                        local_offset++;
                    }
                    else if(q.result != "" && this -> lookup_table.find(q.result) == this -> lookup_table.end() && isVariable(q.result)) {
                        this -> lookup_table[q.result] = subroutine_entry(q.result, -stack_offset*local_offset);
                        local_offset++;
                    }
                    cout<<" :"<<stack_offset*(local_offset-1)<<endl;
                }
            }
        }

        this -> total_space = stack_offset * local_offset;   // total space occupied by callee saved registers + locals + temporaries
    }
};

vector<subroutine_table* > sub_tables;
void gen_basic_block(vector<quad> BB, subroutine_table*);
void gen_tac_basic_block(vector<quad> subroutine, subroutine_table*);
 void append_ins(instruction ins);


void append_ins(instruction ins);

void get_tac_subroutines();                             // generates all the subroutines from the tac
void gen_tac_basic_block(vector<quad>, subroutine_table*);      // generates all the basic blocks from subroutines

bool isVariable(string s);
bool isMainFunction(string s);
// string get_func_name(string s);          

// void gen_global();                                      // generates code for the global region
void gen_text();                                        // generates code for the text region
void gen_fixed_subroutines();                           // generates some fixed subroutines
void gen_subroutine(vector<quad> subroutine);           // generates code for individual subroutines
    // generates code for basic blocks

bool isVariable(string s) {   // if the first character is a digit/-/+, then it is a constant and not a variable
    // Undefined behaviour when s is ""
    if(s == "") {
        cout << "Empty string is neither constant/variable. Aborting...";
        exit(1);
    }
    return !(s[0] >= '0' && s[0] <= '9') && (s[0] != '-') && (s[0] != '+');
}

bool isMainFunction(string s) {
    // string sub = "";
    // for(int i = s.length() - 1; i >= 0; i--) {
    //     if(s[i] == '.') {
    //         break;
    //     }
    //     else {
    //         sub += s[i];
    //     }
    // }

    // return sub == "][gnirtS@niam";
    return s == "main";
}

// string get_func_name(string s) {
//     if(func_name_map.find(s) == func_name_map.end()) {
//         func_count++;
//         func_name_map[s] = "func" + to_string(func_count);
//     }

//     return func_name_map[s];
// }


void gen_global() {
    // @TODO
    instruction ins;
    ins = instruction(".data", "", "", "", "segment");
    cout<<"Done at line no. 286"<<endl;
    code.push_back(ins);

    ins = instruction("integer_format:", ".asciz", "\"%ld\\n\"", "", "ins");
    code.push_back(ins);

    ins = instruction(".global", "main", "", "", "segment");      // define entry point
    code.push_back(ins);
}

/*
def get(int a )->int:
    a = 5;
    return a

def main():
    print(get(3))
*/

//quad(result, arg1, op, arg2, insType)
//insType = binary, unary, assignment, conditional, cast, store, load, func_call, goto, begin_func, end_func, return, shift_pointer, push_param, pop_param, return_val
vector<quad>tacQuads = {
    quad("", "get", "begin_func", "", "begin_func"),
    quad("t0","","","","pop_param"),
    quad("a", "t0", "=", "", "assignment"),
    quad("", "a", "return", "", "return_val"),
    quad("", "", "return", "", "return"),
    quad("", "get", "end_func", "", "end_func"),
    quad("","main", "begin_func", "", "begin_func"),
    quad("", "3", "push_param", "", "push_param"),
    quad("", "get", "func_call", "", "func_call"),
    quad("t1", "return_val", "", "", "assignment"),
    quad("","t1","push_param","","push_param"),
    quad("", "print", "", "1", "func_call"),
    quad("","main", "end_func", "", "end_func"),
};

// vector<quad>tacQuads = {
//     quad("","main", "begin_func", "", "begin_func"),
//     quad("a", "3", "=", "", "assignment"),
//     quad("b", "4", "=","","assignment"),
//     quad("c", "5", "=", "", "assignment"),
//     quad("d", "6", "=", "", "assignment"),
//     quad("temp1", "a", ">", "b", "binary"),
//     quad("", "temp1", "ifTrue", "L1", "conditional"),
//     quad("x", "c", "+", "d", "binary"),
//     quad("", "", "", "L2", "goto"),
//     quad("", "L1", "", "", "label"),
//     quad("x", "c", "-", "d", "binary"),
//     quad("", "L2", "", "", "label"),
//     quad("y", "a", "+", "b", "binary"),
//     quad("temp2", "x", "+", "y", "binary"),
//     quad("","temp2","","","push_param"),
//     quad("","print","","1","func_call"),
//     quad("","main", "end_func", "", "end_func"),
// };

void append_ins(instruction ins) {
    code.push_back(ins);
}

void get_tac_subroutines() {
    vector<quad> subroutine;

    bool func_started = false;
   
    for(auto q : tacQuads) {
        cout<<q.arg1<<endl;
        if(q.op == "begin_func") {
            func_started = true;
        }

        if(func_started) {
            subroutine.push_back(q);
        }

        if(q.op == "end_func") {
            func_started = false;
            if(subroutine.size()){
                subroutines.push_back(subroutine);
                subroutine.clear();
            }
        }
    }
}

void gen_basic_block(vector<quad> BB, subroutine_table* sub_table) {
    for(quad q : BB) {
        vector<instruction> insts;
        if(q.insType == "conditional"){
            int x = sub_table -> lookup_table[q.arg1].offset;
            int y = q.abs_jump;
            insts = make_x86_code(q, x, y);
        }
        else if(q.insType == "goto"){
            insts = make_x86_code(q, q.abs_jump);
        }
        else if(q.insType == "binary"){
            int z = sub_table -> lookup_table[q.result].offset;
            int x = sub_table -> lookup_table[q.arg1].offset;
            int y = sub_table -> lookup_table[q.arg2].offset;
            insts = make_x86_code(q, x, y, z);            
        }
        else if(q.insType == "unary"){    // b(y) = op a(x)
            int y = sub_table -> lookup_table[q.result].offset;
            int x = sub_table -> lookup_table[q.arg1].offset;
            insts = make_x86_code(q, x, y);           
        }
        else if(q.insType == "assignment"){   // b(y) = a(x)
            int y = sub_table -> lookup_table[q.result].offset;
            int x = sub_table -> lookup_table[q.arg1].offset;
            insts = make_x86_code(q, x, y);                
        }
        else if(q.insType == "store"){        // *(r(z) + a2) = a1(x)
            int x = sub_table -> lookup_table[q.arg1].offset;
            int y = sub_table -> lookup_table[q.arg2].offset;   // always 0 since q.arg2 contains a constant always
            int z = sub_table -> lookup_table[q.result].offset;

            insts = make_x86_code(q, x, y, z);
        }
        else if(q.insType == "load"){         // r(z) = *(a1(x) + a2)
            int x = sub_table -> lookup_table[q.arg1].offset;
            int y = sub_table -> lookup_table[q.arg2].offset; // always 0 since q.arg2 contains a constant always
            int z = sub_table -> lookup_table[q.result].offset;

            insts = make_x86_code(q, x, y, z);
        }
        else if(q.insType == "cast"){         // b(y) = (op) a(x)
            int x = sub_table -> lookup_table[q.arg1].offset;
            int y = sub_table -> lookup_table[q.result].offset;
            insts = make_x86_code(q, x, y);
        }
        else if(q.insType == "push_param"){   // push_param a1(x)
            int x = sub_table -> lookup_table[q.arg1].offset;
            sub_table -> number_of_params++;
            insts = make_x86_code(q, x, sub_table -> number_of_params);
        }
        else if(q.insType == "pop_param"){   // r(x) = pop_param
            // no need to do anything really

            insts = make_x86_code(q);
        }
        else if(q.insType == "func_call") {
            insts = make_x86_code(q, sub_table -> number_of_params);
            sub_table -> number_of_params = 0;          // reset variable
        }
        else if(q.insType == "return_val") {
            insts = make_x86_code(q, sub_table -> lookup_table[q.result].offset);
        }
        else if(q.insType == "begin_func") {  // manage callee saved registers
            if(isMainFunction(q.arg1)) {
                sub_table -> is_main_function = 1;
            }
            insts = make_x86_code(q, sub_table -> total_space - 8 * stack_offset, sub_table -> is_main_function);        // space of 8 registers is not considered
        }
        else if(q.insType == "end_func") {    // clean up activation record
            // ideally only reaches this place in a void function
            insts = make_x86_code(q, sub_table -> is_main_function, sub_table -> total_space - 8 * stack_offset);
        }
        else if(q.insType == "shift_pointer") {       // no need to do anything really
            insts = make_x86_code(q);
        }
        else if(q.insType == "return") {     // clean up activation record
            insts = make_x86_code(q, sub_table -> total_space - 8 * stack_offset, sub_table -> lookup_table[q.arg1].offset);
        }
        else{
            insts = make_x86_code(q);
        }

        // append all the instructions finally
        for(instruction ins : insts) {
            append_ins(ins);
        }
    }
}


void gen_tac_basic_block(vector<quad> subroutine, subroutine_table* sub_table) {    // generates basic blocks from subroutines
    set<int> leaders;
    vector<quad > BB;

    int base_offset = subroutine[0].ins_line;
    leaders.insert(base_offset);

    for(quad q : subroutine) {
        if(q.insType == "conditional"|| q.insType == "goto") {
            leaders.insert(q.abs_jump);
            leaders.insert(q.ins_line + 1);
        }
        else if(q.insType == "func_call") {
            leaders.insert(q.ins_line);
            leaders.insert(q.ins_line + 1); // call func is made of a singular basic block
        }
    }

    vector<int> ascending_leaders;
    for(int leader : leaders) { 
        ascending_leaders.push_back(leader); 
    }
    
    int prev_leader = ascending_leaders[0];
    for(int i = 1; i < ascending_leaders.size(); i++) {
        BB.clear();
        
        for(int j = prev_leader; j < ascending_leaders[i]; j++) {
            BB.push_back(subroutine[j - base_offset]);
        }
        prev_leader = ascending_leaders[i];

        gen_basic_block(BB, sub_table);
    }

    BB.clear();
    int final_leader = ascending_leaders[ascending_leaders.size() - 1];
    for(int i = final_leader; i - base_offset < subroutine.size(); i++) {
        BB.push_back(subroutine[i - base_offset]);
    }

    gen_basic_block(BB, sub_table);
}

void gen_fixed_subroutines() {
    func_name_map["print"] = "print";
    func_name_map["allocmem"] = "allocmem";
}



void gen_text() {
    instruction ins(".text", "", "", "", "segment");
    code.push_back(ins);

    gen_fixed_subroutines();

    get_tac_subroutines();      // get the subroutines from entire TAC

    for(auto subroutine : subroutines) {
        subroutine_table* sub_table = new subroutine_table();
        sub_table -> construct_subroutine_table(subroutine);

        sub_tables .push_back(sub_table);
        gen_tac_basic_block(subroutine, sub_table);
    }
}

vector<instruction> make_x86_code(quad q, int x, int y, int z){

    vector<instruction> insts;
    instruction ins;

    // if(q.code == ""){
    //     return insts;        
    // }
    // else{
    //     if(q.insType != "shift_pointer" && q.insType != "pop_param"){
    //         ins = instruction("", "", "", "", "comment", q.code.substr(2, q.code.size() - 2));
    //         insts.push_back(ins);
    //     }
    // }

    if(q.is_target) {   // if this is a target, a label needs to be added
        ins = instruction("", "L" + to_string(q.ins_line), "", "", "label");
        insts.push_back(ins);
    }
    if(q.insType == "binary"){            // c(z) = a(x) op b(y)
        // Load value of a into %rax
        if(q.op == "+"){
            cout << "Adding " << q.arg1 << " and " << q.arg2 << endl;
           
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");

            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);
            if(!isVariable(q.arg2)){
                ins = instruction("add", "$" + q.arg2, "%rdx");
            }
            else{
                ins = instruction("add", to_string(y) + "(%rbp)", "%rdx");
            }
        }
        else if(q.op == "-"){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);
            if(!isVariable(q.arg2)){
                ins = instruction("sub", "$" + q.arg2, "%rdx");
            }
            else{
                ins = instruction("sub", to_string(y) + "(%rbp)", "%rdx");
            }
        }
        else if(q.op == "*"){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);
            if(!isVariable(q.arg2)){
                ins = instruction("imul", "$" + q.arg2, "%rdx");
            }
            else{
                ins = instruction("imul", to_string(y) + "(%rbp)", "%rdx");
            }
        }
        else if(q.op == "/"){
            if(!isVariable(q.arg1)){   // arg1 is a literal
                ins = instruction("movq", "$" + q.arg1, "%rax");
                insts.push_back(ins);
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rax");
                insts.push_back(ins);                
            }
            ins = instruction("cqto");
            insts.push_back(ins);

            if(!isVariable(q.arg2)){  // arg2 is a literal
                ins = instruction("movq", "$" + q.arg2, "%rbx");
            }
            else{
                ins = instruction("movq", to_string(y) + "(%rbp)", "%rbx");
            }
            insts.push_back(ins);
            ins = instruction("idiv", "%rbx", "");
            insts.push_back(ins);
            ins = instruction("movq", "%rax", "%rdx");
        }
        else if(q.op == "%"){
            if(!isVariable(q.arg1)){   // arg1 is a literal
                ins = instruction("movq", "$" + q.arg1, "%rax");
                insts.push_back(ins);
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rax");
                insts.push_back(ins);                
            }
            ins = instruction("cqto");
            insts.push_back(ins);

            if(!isVariable(q.arg2)){  // arg2 is a literal
                ins = instruction("movq", "$" + q.arg2, "%rbx");
            }
            else{
                ins = instruction("movq", to_string(y) + "(%rbp)", "%rbx");
            }
            insts.push_back(ins);
            ins = instruction("idiv", "%rbx", "");
        }
        else if(q.op == "<<"){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);
            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg2, "%rcx");
            }
            else{
                ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
            }
            insts.push_back(ins);
            ins = instruction("sal", "%cl", "%rdx");
        }
        else if(q.op == ">>"){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);
            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg2, "%rcx");
            }
            else{
                ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
            }
            insts.push_back(ins);
            ins = instruction("sar", "%cl", "%rdx");
        }
        else if(q.op == ">>>"){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);
            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg2, "%rcx");
            }
            else{
                ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
            }
            insts.push_back(ins);
            ins = instruction("shr", "%cl", "%rdx");
        }
        else if(q.op == ">"){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);

            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg2, "%rcx");
            }
            else{
                ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
            }
            insts.push_back(ins);
            ins = instruction("cmp", "%rdx", "%rcx");
            insts.push_back(ins);
            ins = instruction("jl", "1f");  // true
            insts.push_back(ins);
            ins = instruction("movq", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f"); // false
            insts.push_back(ins);
            ins = instruction("", "1", "", "", "label");
            insts.push_back(ins);
            ins = instruction("movq", "$1", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f");
            insts.push_back(ins);
            ins = instruction("", "2", "", "", "label");
        }
        else if(q.op == "<"){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);

            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg2, "%rcx");
            }
            else{
                ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
            }
            insts.push_back(ins);
            ins = instruction("cmp", "%rdx", "%rcx");
            insts.push_back(ins);
            ins = instruction("jg", "1f");  // true
            insts.push_back(ins);
            ins = instruction("movq", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f"); // false
            insts.push_back(ins);
            ins = instruction("", "1", "", "", "label");
            insts.push_back(ins);
            ins = instruction("movq", "$1", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f");
            insts.push_back(ins);
            ins = instruction("", "2", "", "", "label");
        }
        else if(q.op == ">="){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);

            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg2, "%rcx");
            }
            else{
                ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
            }
            insts.push_back(ins);
            ins = instruction("cmp", "%rdx", "%rcx");
            insts.push_back(ins);
            ins = instruction("jle", "1f");  // true
            insts.push_back(ins);
            ins = instruction("movq", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f"); // false
            insts.push_back(ins);
            ins = instruction("", "1", "", "", "label");
            insts.push_back(ins);
            ins = instruction("movq", "$1", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f");
            insts.push_back(ins);
            ins = instruction("", "2", "", "", "label");
        }
        else if(q.op == "<="){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);

            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg2, "%rcx");
            }
            else{
                ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
            }
            insts.push_back(ins);
            ins = instruction("cmp", "%rdx", "%rcx");
            insts.push_back(ins);
            ins = instruction("jge", "1f");  // true
            insts.push_back(ins);
            ins = instruction("movq", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f"); // false
            insts.push_back(ins);
            ins = instruction("", "1", "", "", "label");
            insts.push_back(ins);
            ins = instruction("movq", "$1", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f");
            insts.push_back(ins);
            ins = instruction("", "2", "", "", "label");
        }
        else if(q.op == "=="){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);

            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg2, "%rcx");
            }
            else{
                ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
            }
            insts.push_back(ins);
            ins = instruction("cmp", "%rdx", "%rcx");
            insts.push_back(ins);
            ins = instruction("je", "1f");  // true
            insts.push_back(ins);
            ins = instruction("movq", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f"); // false
            insts.push_back(ins);
            ins = instruction("", "1", "", "", "label");
            insts.push_back(ins);
            ins = instruction("movq", "$1", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f");
            insts.push_back(ins);
            ins = instruction("", "2", "", "", "label");
        }
        else if(q.op == "!="){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);

            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg2, "%rcx");
            }
            else{
                ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
            }
            insts.push_back(ins);
            ins = instruction("cmp", "%rdx", "%rcx");
            insts.push_back(ins);
            ins = instruction("jne", "1f");  // true
            insts.push_back(ins);
            ins = instruction("movq", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f"); // false
            insts.push_back(ins);
            ins = instruction("", "1", "", "", "label");
            insts.push_back(ins);
            ins = instruction("movq", "$1", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f");
            insts.push_back(ins);
            ins = instruction("", "2", "", "", "label");
        }
        else if(q.op == "&"){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);
            if(!isVariable(q.arg2)){
                ins = instruction("and", "$" + q.arg2, "%rdx");
            }
            else{
                ins = instruction("and", to_string(y) + "(%rbp)", "%rdx");
            }     
        }
        else if(q.op == "|"){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);
            if(!isVariable(q.arg2)){
                ins = instruction("or", "$" + q.arg2, "%rdx");
            }
            else{
                ins = instruction("or", to_string(y) + "(%rbp)", "%rdx");
            }     
        }
        else if(q.op == "^"){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);
            if(!isVariable(q.arg2)){
                ins = instruction("xor", "$" + q.arg2, "%rdx");
            }
            else{
                ins = instruction("xor", to_string(y) + "(%rbp)", "%rdx");
            }
        }
        else if(q.op == "&&"){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);
            ins = instruction("cmp", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("je", "1f");
            insts.push_back(ins);
            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg2, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(y) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);
            ins = instruction("cmp", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("je", "1f");
            insts.push_back(ins);
            ins = instruction("movq", "$1", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f");
            insts.push_back(ins);
            ins = instruction("", "1", "", "", "label");
            insts.push_back(ins);
            ins = instruction("movq", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("", "2", "", "", "label");
        }
        else if(q.op == "||"){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);
            ins = instruction("cmp", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("jne", "1f");     // true
            insts.push_back(ins);
            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg2, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(y) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);
            ins = instruction("cmp", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("jne", "1f");     // true
            insts.push_back(ins);
            ins = instruction("movq", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f");     // false
            insts.push_back(ins);
            ins = instruction("", "1", "", "", "label");
            insts.push_back(ins);
            ins = instruction("movq", "$1", "%rdx");
            insts.push_back(ins);
            ins = instruction("", "2", "", "", "label");
        }
        insts.push_back(ins);
        
        ins = instruction("movq", "%rdx", to_string(z) + "(%rbp)");
        insts.push_back(ins);
    }
    else if(q.insType == "unary"){        // b(y) = op a(x)
        if(q.op == "~"){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);
            ins = instruction("neg", "%rdx", "");
        }
        else if(q.op == "!"){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
            insts.push_back(ins);
            ins = instruction("not", "%rdx", "");
        }
        else if(q.op == "-"){
            ins = instruction("xor", "%rdx", "%rdx");
            insts.push_back(ins);
            if(!isVariable(q.arg1)){
                ins = instruction("sub", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("sub", to_string(x) + "(%rbp)", "%rdx");
            }
        }
        else if(q.op == "+"){
            ins = instruction("xor", "%rdx", "%rdx");
            insts.push_back(ins);
            if(!isVariable(q.arg1)){
                ins = instruction("add", "$" + q.arg1, "%rdx");
            }
            else{
                ins = instruction("add", to_string(x) + "(%rbp)", "%rdx");
            }
        }
        insts.push_back(ins);
        
        ins = instruction("movq", "%rdx", to_string(y) + "(%rbp)");
        insts.push_back(ins);
    }
    else if(q.insType == "assignment"){   // b(y) = a(x)
        if(!isVariable(q.arg1)){
            ins = instruction("movq", "$" + q.arg1, to_string(y) + "(%rbp)");
            insts.push_back(ins);
        }
        else{
            ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            insts.push_back(ins);            
            ins = instruction("movq", "%rdx", to_string(y) + "(%rbp)");
            insts.push_back(ins);
        }
    }
    else if(q.insType == "conditional"){  // if_false/if_true(op) a(x) goto y
        if(!isVariable(q.arg1)){
            ins = instruction("movq", "$" + q.arg1, "%rdx");
        }
        else{
            ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
        }
        insts.push_back(ins);
        ins = instruction("cmp", "$0", "%rdx");
        insts.push_back(ins);
        
        if(q.op == "if_false"){
            ins = instruction("je", "L" + to_string(y));
        }
        else if(q.op == "if_true"){
            ins = instruction("jne", "L" + to_string(y));
        }
        insts.push_back(ins);
    } 
    else if(q.insType == "goto"){         // goto (x)
        ins = instruction("jmp", q.arg2);
        insts.push_back(ins);
    }
    else if(q.insType == "store"){        // *(r(z) + a2) = a1(x)
        if(!isVariable(q.arg1)){
            ins = instruction("movq", "$" + q.arg1, "%rax");
        }
        else{
            ins = instruction("movq", to_string(x) + "(%rbp)", "%rax");
        }
        insts.push_back(ins);
        
        ins = instruction("movq", to_string(z) + "(%rbp)", "%rdx");
        insts.push_back(ins);

        if(q.arg2 == "" || !isVariable(q.arg2)) {
            ins = instruction("movq", "%rax", q.arg2 + "(%rdx)");
            insts.push_back(ins);
        }
        else {
            cout << "Unknown TAC `" << q.code << "`. Cannot make load from this code!" << endl;
            exit(1);  
        }
    }
    else if(q.insType == "load"){         // r(z) = *(a1(x) + a2(y))
        ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
        insts.push_back(ins);

        if(q.arg2 == "" || !isVariable(q.arg2)) {
            ins = instruction("movq", q.arg2 + "(%rdx)", "%rdx");
            insts.push_back(ins);
        }
        else {
            cout << "Unknown TAC `" << q.code << "`. Cannot make load from this code!" << endl;
            exit(1);
        }

        ins = instruction("movq", "%rdx", to_string(z) + "(%rbp)");
        insts.push_back(ins);
    }
    else if(q.insType == "begin_func") {  // perform callee duties
        cout<<"inside begin function "<< " x = "<<x<<" y(check for main)= "<<y<<endl;
        if(y == 1) {        // make start label if it is the main function
            ins = instruction("", "main", "", "", "label");
            insts.push_back(ins);
        }
        else{
            ins = instruction("", q.arg1, "", "", "label");     // add label
            insts.push_back(ins);
        }


        ins = instruction("pushq", "%rbp");      // old base pointer
        insts.push_back(ins);
        ins = instruction("movq", "%rsp", "%rbp");    // shift base pointer to the base of the new activation frame
        insts.push_back(ins);
        ins = instruction("pushq", "%rbx");
        insts.push_back(ins);
        ins = instruction("pushq", "%rdi");
        insts.push_back(ins);
        ins = instruction("pushq", "%rsi");
        insts.push_back(ins);
        ins = instruction("pushq", "%r12");
        insts.push_back(ins);
        ins = instruction("pushq", "%r13");
        insts.push_back(ins);
        ins = instruction("pushq", "%r14");
        insts.push_back(ins);
        ins = instruction("pushq", "%r15");
        insts.push_back(ins);

        // shift stack pointer to make space for locals and temporaries, ignore if no locals/temporaries in function
        if(x > 0) {
            ins = instruction("sub", "$" + to_string(x), "%rsp");
            insts.push_back(ins);
        }
    }
    else if(q.insType == "return") {    // clean up activation record
        if(q.arg1 != "") {      // Load %rax with the return value if non-void function
            if(!isVariable(q.arg1)) {
                ins = instruction("movq", "$" + q.arg1, "%rax");
            }
            else {
                ins = instruction("movq", to_string(y) + "(%rbp)", "%rax");
            }
            insts.push_back(ins);
        }
        
        ins = instruction("add", "$" + to_string(x), "%rsp");   // delete all local and temporary variables
        insts.push_back(ins);
        ins = instruction("popq", "%r15");                      // restore old register values
        insts.push_back(ins);
        ins = instruction("popq", "%r14");
        insts.push_back(ins);
        ins = instruction("popq", "%r13");
        insts.push_back(ins);
        ins = instruction("popq", "%r12");
        insts.push_back(ins);
        ins = instruction("popq", "%rsi");
        insts.push_back(ins);
        ins = instruction("popq", "%rdi");
        insts.push_back(ins);
        ins = instruction("popq", "%rbx");
        insts.push_back(ins);
        ins = instruction("popq", "%rbp");
        insts.push_back(ins);

        ins = instruction("ret");
        insts.push_back(ins);
    }
    else if(q.insType == "end_func") {
        cout<<"inside end function "<< " x(check for main) = "<<x<<" y= "<<y<<endl;
        if(x == 1) {        // if main function
            ins = instruction("movq", "$60", "%rax");
            insts.push_back(ins);
            ins = instruction("xor", "%rdi", "%rdi");
            insts.push_back(ins);
            ins = instruction("syscall");
            insts.push_back(ins);
        }
        else {              // otherwise we perform usual callee clean up
            // end func cannot return any values    
            ins = instruction("add", "$" + to_string(y), "%rsp");   // delete all local and temporary variables
            insts.push_back(ins);
            ins = instruction("popq", "%r15");                      // restore old register values
            insts.push_back(ins);
            ins = instruction("popq", "%r14");
            insts.push_back(ins);
            ins = instruction("popq", "%r13");
            insts.push_back(ins);
            ins = instruction("popq", "%r12");
            insts.push_back(ins);
            ins = instruction("popq", "%rsi");
            insts.push_back(ins);
            ins = instruction("popq", "%rdi");
            insts.push_back(ins);
            ins = instruction("popq", "%rbx");
            insts.push_back(ins);
            ins = instruction("popq", "%rbp");
            insts.push_back(ins);
            ins = instruction("ret");
            insts.push_back(ins);
        }
    }
    else if(q.insType == "shift_pointer") {    // r(z) = r(x) + a1(y)
        // no need to do anything really for x86
    }
    else if(q.insType == "func_call") {
        if(x == 0) {        // if function is called without any parameters, we have yet to perform caller responsibilities
            ins = instruction("pushq", "%rax");
            insts.push_back(ins);
            ins = instruction("pushq", "%rcx");
            insts.push_back(ins);
            ins = instruction("pushq", "%rdx");
            insts.push_back(ins);
            ins = instruction("pushq", "%r8");
            insts.push_back(ins);
            ins = instruction("pushq", "%r9");
            insts.push_back(ins);
            ins = instruction("pushq", "%r10");
            insts.push_back(ins);
            ins = instruction("pushq", "%r11");
            insts.push_back(ins);
        }
        ins = instruction("call", q.arg1);      // call the function
        insts.push_back(ins);

        if(q.arg1 == "print") {          // deal specially with print
            ins = instruction("add", "$8", "%rsp");
            insts.push_back(ins);
        }
        else if(q.arg1 == "allocmem") {
            ins = instruction("add", "$8", "%rsp");             // deal specially with allocmem
            insts.push_back(ins);
        }
        else if(x > 0) {                             // pop the parameters
            ins = instruction("add", "$" + to_string(x*stack_offset), "%rsp");
            insts.push_back(ins);
        }
    }
    else if(q.insType == "return_val") {
        // move the return value stored in %rax to the required location
        if(q.result != "") {      // if the function returns a value
            ins = instruction("mov", "%rax", to_string(x) + "(%rbp)");
            insts.push_back(ins);
        }

        // restore original state of registers
        ins = instruction("popq", "%r11");
        insts.push_back(ins);
        ins = instruction("popq", "%r10");
        insts.push_back(ins);
        ins = instruction("popq", "%r9");
        insts.push_back(ins);
        ins = instruction("popq", "%r8");
        insts.push_back(ins);
        ins = instruction("popq", "%rdx");
        insts.push_back(ins);
        ins = instruction("popq", "%rcx");
        insts.push_back(ins);
        ins = instruction("popq", "%rax");
        insts.push_back(ins);
    }
    else if(q.insType == "push_param"){   // pushq a(x) || pushq const
        if(y == 1) {        // first parameter, perform caller saved registers
            ins = instruction("pushq", "%rax");
            insts.push_back(ins);
            ins = instruction("pushq", "%rcx");
            insts.push_back(ins);
            ins = instruction("pushq", "%rdx");
            insts.push_back(ins);
            ins = instruction("pushq", "%r8");
            insts.push_back(ins);
            ins = instruction("pushq", "%r9");
            insts.push_back(ins);
            ins = instruction("pushq", "%r10");
            insts.push_back(ins);
            ins = instruction("pushq", "%r11");
            insts.push_back(ins);
        }
        if(!isVariable(q.arg1)) {  // it is just a constant
            ins = instruction("pushq", "$" + q.arg1, "");
            insts.push_back(ins);
        } 
        else {
            ins = instruction("pushq", to_string(x) + "(%rbp)"); // load rbp + x
            insts.push_back(ins);    
        }
    }
    else if(q.insType == "cast"){     // r(y) = (op) a(x)
        if(!isVariable(q.arg1)) {  // it is a constant
            ins = instruction("movq", "$" + q.arg1, "%rdx");
        } 
        else {
            ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx"); // load rbp + x
        }
        insts.push_back(ins);    
        ins = instruction("movq", "%rdx", to_string(y) + "(%rbp)");
        insts.push_back(ins);    
    }
    else if(q.insType == "label"){    // label Lx
        ins = instruction("", q.arg1, "", "", "label");
        insts.push_back(ins);
    }

    return insts;
}


void print_code(string asm_file) {
    ofstream out(asm_file);
    cout<<"printing code"<<endl;
    if(asm_file == "") {
        for(auto ins : code) {
            out<<ins.code;
        }
    }
    else {
        for(auto ins : code) {
            out<<ins.code;
        }
    }

    ifstream print_func("print_func.s");
    string line;

    while(getline(print_func, line)){
        out << line << '\n';
    }

    ifstream alloc_mem("allocmem.s");
    while(getline(alloc_mem, line)) {
        out << line << '\n';
    }
}


