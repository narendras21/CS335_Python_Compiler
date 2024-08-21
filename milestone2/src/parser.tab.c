/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

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

//

//  vector<quad>tacQuads = {
//   quad("","main", "begin_func", "", "begin_func"),
//      quad("a", "3", "=", "", "assignment"),
//      quad("b", "4", "=","","assignment"),
//      quad("c", "5", "=", "", "assignment"),
//      quad("d", "6", "=", "", "assignment"),
//      quad("temp1", "a", ">", "b", "binary"),
//      quad("", "temp1", "ifTrue", "L1", "conditional"),
//      quad("x", "c", "+", "d", "binary"),
//      quad("", "", "", "L2", "goto"),
//      quad("", "L1", "", "", "label"),
//      quad("x", "c", "-", "d", "binary"),
//      quad("", "L2", "", "", "label"),
//      quad("y", "a", "+", "b", "binary"),
//      quad("temp2", "x", "+", "y", "binary"),
//      quad("","temp2","","","push_param"),
//      quad("","print","","1","func_call"),
//      quad("","main", "end_func", "", "end_func"),
//  };

 vector<quad>tacQuads = {
    quad("","main","begin_func","","begin_func"),
    quad("b","10","=","","assignment"),
    quad("a","18","=","","assignment"),
    quad("t0","a","+","b","binary"),
    quad("a","t0","=","","assignment"),
    quad("","a","","","push_param"),
    quad("","print","","1","func_call"),
    quad("","","","","return_val"),
    quad("","","end_func","","end_func")
 };


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




////////////////////////////////////////////////////////////////
//end modifying
////////////////////////////////////////////////////////////////

int yylex();
void yyerror(const char *s);
void tacToAssembly(ofstream& file, FILE*assem);
string instrType(string op);


map<int, pair<string, vector<int>>> AST;
int nodeCount = -1;

void ParentToChild(int parent, int child) {
  (AST[parent].second).push_back(child);
}

int nodeInit(string nodeName) {
    nodeCount++;
    string name = nodeName;
    vector<int> children;
    AST[nodeCount].first = name;
    AST[nodeCount].second = children;
    return nodeCount;
}


void write_gv(string &filename) {
  ofstream out(filename);
  if (!out.is_open()) {
    cerr << "ERROR: gv file can't be opened ";
    return;
  }

  out << "digraph AST {\n";
  
  for (const auto &node : AST) {
    int nodeId = node.first;
    string nodeName = node.second.first;
    vector<int> nodeChildren = node.second.second;

    out << nodeId << " [label=\"" << nodeName << "\"];\n";
    for (auto c : nodeChildren) {
      if (c>=0) {
        out << nodeId << "->" << c << ";\n";
      }
    }
  }

  out << "}";
  out.close();
}

int debug = 0;
void debugging(string msg, int mode){
    // if(debug == mode){
    //     cout <<"||->"<< msg << endl;
    // }

}

int getSize(string type){
    if(type == "int"){return 4;}
    else if(type == "float"){return 8;}
    else if(type == "str"){return 256;}
    else if(type == "string"){return 256;}
    else if(type == "bool"){return 1;}
    else if(type.compare(0,4,"list") ==0){
        return 8; //pointer 
    }
    else if(type=="none") {return 1;}
    else if(type =="class"){return 100;}
    else {
        return 8;
    }
}

//Sym entry globals
int num_args = 0;
int param_num = -1;

class SymbolEntry {
      public:
        string token;
        string type;
        int size;
        string scope_name;
        int offset;
        int lineno;

        //function
        string rtype;
        int num_args;
        int arg_num;

        string par_arg_shape; //to get shape of parameters of args

        
        //constructor
        SymbolEntry(){ 
        }

        SymbolEntry(string token, string type, int size, int offset, string scope_name, int lineno, int num_args, int arg_num){
          this->token = token;
          this->type = type;
          this->size = size;
          this->offset = offset;
          this->scope_name = scope_name;
          this->lineno = lineno;
          this->num_args= num_args;
          this->arg_num = arg_num;
          
        }
        void print_entry(){
          cout << token << " " << type << " " << size << " " << offset << " " << scope_name << " " << lineno << " "<<num_args << " "<<arg_num<< endl;
        }
};

string found_table;

class SymbolTable {
    public:
        map <pair<string,string>, SymbolEntry> Table;
        SymbolTable* Parent;
        string TableName;
        string Signature;
        vector<SymbolTable*> childTables;
        int level_no;

        //puts in entry into this symbol table
        void entry(string lexeme, string sig, string token, string type, int size,  int offset, string scope_name, int line, int num_args, int arg_num){
            pair<string, string> id = {lexeme, sig};
            Table[id] = SymbolEntry(token, type, size, offset, scope_name, line, num_args, arg_num);
        }

        SymbolTable(){}
        SymbolTable(SymbolTable* P, string name, string signature){
            if(!P){
                level_no = 0;
                Parent = NULL;
                TableName = name;
                Signature = signature;
            }
            else{
                level_no = P->level_no + 1;
                Parent = P;
                P->childTables.push_back(this);
                TableName = name;
                Signature = signature;
            }
        }

        SymbolEntry* lookup(pair<string,string>id){
            for(auto it=this; it!=NULL; it=it->Parent){
                // pair<string, string> id = {lexeme, signature};
                if(it->Table.find(id) != it->Table.end()){
                    found_table = it->TableName;
                    // cout << "fouond_table " << found_table << endl;
                    return &(it->Table[id]);
                }
            }
            return NULL;
        }  

        // SymbolEntry* funcLookup(string lexeme){
        //     for(auto it=this; it!=NULL; it=it->Parent){
        //         if(it->Table.find(lexeme) != it->Table.end()){
        //             return &(it->Table[lexeme]);
        //         }
        //     }
        //     return NULL;
        // }

        // SymbolEntry* findMethod(string method){
        //     if(Table.find(method)!= Table.end()){
        //         //found
        //         return &(Table[method]);
        //     }
        //     return NULL;
        // }     

        void print_table(){
            cout << "table name: " << TableName << endl;
            for(auto it=Table.begin(); it!=Table.end(); it++){
                cout<<it->first.first << "||" << it->first.second <<": ";
                it->second.print_entry();
            }
            if(!childTables.empty()){
                cout << "\nchild table(s) of: " << TableName << endl;
                    for( auto it: childTables){
                        // it->print_table();
                        cout << "name: "<< it->TableName << endl;
                    }
                    cout << endl;
            }
        }

        // string parShape(string func_name){
        //     //func_name assumed to exist already
        //     SymbolTable* funcTable;
        //     int flag = 0;
        //     for(SymbolTable* it : childTables ){
        //         if(it->TableName == func_name){
        //             funcTable = it;
        //             flag = 1;
        //             break;
        //         }
        //     }

        //     if(!flag){string s("$"); return s;}
        //     map<int, string> temp;
        //     for(auto it=(funcTable->Table).begin(); it!=(funcTable->Table).end(); it++){
        //         if( (it->second).token == "PARAM"){
        //             temp[(it->second).arg_num] = (it->second).type;
        //         }
        //     }
        //     string res = "";
        //     for(auto it = temp.begin(); it!=temp.end(); it++){
        //         res += it->second;
        //     }
        //     return res;

        // }
};

//sym entry globals
SymbolTable* curr_table = new SymbolTable(NULL, "global", "");
stack<SymbolTable*> tableStk;

int offset = 0;
stack<int> offsetStk;

string curr_scope_name = "global";
stack<string> scopeStk;

vector<SymbolTable*> TablesList (1,curr_table);
// TablesList.push_back(curr_table);  //gives error

//vector of (lexeme,lineno), (type, param_num)
vector< pair< pair<string,int>, pair<string, int> >> fparams;

//vector of (lexeme, (type, arg_num) )
vector< pair<string, pair<string, int>>> fargs;

//vector (funcname, scope_name)
vector< pair<string, string> > func_list;

char curr_return_type[100];

// list of classes in what???
//vector (classname, scope_name)
vector< pair<string, string> > class_list;


SymbolTable* findTable(string tableName, string signature){
     for( auto it: TablesList){
        if(it->TableName == tableName && it->Signature == signature){
            return it;
        }
    }
    return NULL;
}

int label_count = 0;
string getLabel(){
    return "L" + to_string(label_count++);
}
int temp_count = 0;
string getTemp(){
    return "t" + to_string(temp_count++);
}

char* concat(string str1, string str2) {
    if(str1.length()>0){
        str1  = str1 + "\n";
    }
    char* result = new char[str1.length() + str2.length() + 1];
    strcpy(result, str1.c_str());
    strcat(result, str2.c_str());
    return result;
}

string str(char* c){
    string s(c);
    return s;
}

char* cstar(string my_string){
    char* cp = new char[my_string.length() + 1]; 
    strcpy(cp, my_string.c_str());
    return cp;
}

char* nullCST() {
    char* null_string = new char[1];
    null_string[0] = '\0';
    return null_string;
}

string TAC_output = "";

stack<string> breakStk;
stack<string> contStk;

stack<string> endstartStk;
stack<string> successStk;



#line 1739 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NEWLINE = 3,                    /* NEWLINE  */
  YYSYMBOL_AS = 4,                         /* AS  */
  YYSYMBOL_ASYNC = 5,                      /* ASYNC  */
  YYSYMBOL_ASSERT = 6,                     /* ASSERT  */
  YYSYMBOL_AWAIT = 7,                      /* AWAIT  */
  YYSYMBOL_BREAK = 8,                      /* BREAK  */
  YYSYMBOL_CLASS = 9,                      /* CLASS  */
  YYSYMBOL_CONTINUE = 10,                  /* CONTINUE  */
  YYSYMBOL_DEF = 11,                       /* DEF  */
  YYSYMBOL_DEL = 12,                       /* DEL  */
  YYSYMBOL_ELIF = 13,                      /* ELIF  */
  YYSYMBOL_ELSE = 14,                      /* ELSE  */
  YYSYMBOL_EXCEPT = 15,                    /* EXCEPT  */
  YYSYMBOL_FALSE = 16,                     /* FALSE  */
  YYSYMBOL_FINALLY = 17,                   /* FINALLY  */
  YYSYMBOL_FOR = 18,                       /* FOR  */
  YYSYMBOL_FROM = 19,                      /* FROM  */
  YYSYMBOL_GLOBAL = 20,                    /* GLOBAL  */
  YYSYMBOL_IF = 21,                        /* IF  */
  YYSYMBOL_IMPORT = 22,                    /* IMPORT  */
  YYSYMBOL_IN = 23,                        /* IN  */
  YYSYMBOL_IS = 24,                        /* IS  */
  YYSYMBOL_LAMBDA = 25,                    /* LAMBDA  */
  YYSYMBOL_NONE = 26,                      /* NONE  */
  YYSYMBOL_NONLOCAL = 27,                  /* NONLOCAL  */
  YYSYMBOL_PASS = 28,                      /* PASS  */
  YYSYMBOL_RAISE = 29,                     /* RAISE  */
  YYSYMBOL_RETURN = 30,                    /* RETURN  */
  YYSYMBOL_TRUE = 31,                      /* TRUE  */
  YYSYMBOL_TRY = 32,                       /* TRY  */
  YYSYMBOL_WHILE = 33,                     /* WHILE  */
  YYSYMBOL_WITH = 34,                      /* WITH  */
  YYSYMBOL_YIELD = 35,                     /* YIELD  */
  YYSYMBOL_RANGE = 36,                     /* RANGE  */
  YYSYMBOL_LEN = 37,                       /* LEN  */
  YYSYMBOL_PRINT = 38,                     /* PRINT  */
  YYSYMBOL_NAME = 39,                      /* NAME  */
  YYSYMBOL_NUMBER = 40,                    /* NUMBER  */
  YYSYMBOL_NUMBER_INT = 41,                /* NUMBER_INT  */
  YYSYMBOL_NUMBER_FLOAT = 42,              /* NUMBER_FLOAT  */
  YYSYMBOL_INT = 43,                       /* INT  */
  YYSYMBOL_FLOAT = 44,                     /* FLOAT  */
  YYSYMBOL_STR = 45,                       /* STR  */
  YYSYMBOL_BOOL = 46,                      /* BOOL  */
  YYSYMBOL_LIST = 47,                      /* LIST  */
  YYSYMBOL_TRIPLE_DOT = 48,                /* TRIPLE_DOT  */
  YYSYMBOL_MINUS = 49,                     /* MINUS  */
  YYSYMBOL_PLUS = 50,                      /* PLUS  */
  YYSYMBOL_ASTERISK = 51,                  /* ASTERISK  */
  YYSYMBOL_FORWARDSLASH = 52,              /* FORWARDSLASH  */
  YYSYMBOL_DOUBLESLASH = 53,               /* DOUBLESLASH  */
  YYSYMBOL_DOUBLE_STAR = 54,               /* DOUBLE_STAR  */
  YYSYMBOL_NOT = 55,                       /* NOT  */
  YYSYMBOL_OR = 56,                        /* OR  */
  YYSYMBOL_AND = 57,                       /* AND  */
  YYSYMBOL_LT_LT = 58,                     /* LT_LT  */
  YYSYMBOL_GT_GT = 59,                     /* GT_GT  */
  YYSYMBOL_AMPERSAND = 60,                 /* AMPERSAND  */
  YYSYMBOL_BAR = 61,                       /* BAR  */
  YYSYMBOL_CAP = 62,                       /* CAP  */
  YYSYMBOL_TILDE = 63,                     /* TILDE  */
  YYSYMBOL_COLON_EQ = 64,                  /* COLON_EQ  */
  YYSYMBOL_LT = 65,                        /* LT  */
  YYSYMBOL_GT = 66,                        /* GT  */
  YYSYMBOL_LT_EQ = 67,                     /* LT_EQ  */
  YYSYMBOL_GT_EQ = 68,                     /* GT_EQ  */
  YYSYMBOL_EQ_EQ = 69,                     /* EQ_EQ  */
  YYSYMBOL_NOT_EQ = 70,                    /* NOT_EQ  */
  YYSYMBOL_PERCENT = 71,                   /* PERCENT  */
  YYSYMBOL_STRING = 72,                    /* STRING  */
  YYSYMBOL_LPAREN = 73,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 74,                    /* RPAREN  */
  YYSYMBOL_LCURLY = 75,                    /* LCURLY  */
  YYSYMBOL_RCURLY = 76,                    /* RCURLY  */
  YYSYMBOL_LSQUARE = 77,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 78,                   /* RSQUARE  */
  YYSYMBOL_DOT = 79,                       /* DOT  */
  YYSYMBOL_COMMA = 80,                     /* COMMA  */
  YYSYMBOL_COLON = 81,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 82,                 /* SEMICOLON  */
  YYSYMBOL_RARR = 83,                      /* RARR  */
  YYSYMBOL_AMPERSAND_EQ = 84,              /* AMPERSAND_EQ  */
  YYSYMBOL_AT = 85,                        /* AT  */
  YYSYMBOL_AT_EQ = 86,                     /* AT_EQ  */
  YYSYMBOL_CAP_EQ = 87,                    /* CAP_EQ  */
  YYSYMBOL_DOUBLE_SLASH_EQ = 88,           /* DOUBLE_SLASH_EQ  */
  YYSYMBOL_DOUBLE_STAR_EQ = 89,            /* DOUBLE_STAR_EQ  */
  YYSYMBOL_EQUALS = 90,                    /* EQUALS  */
  YYSYMBOL_FORWARDSLASH_EQ = 91,           /* FORWARDSLASH_EQ  */
  YYSYMBOL_LT_GT = 92,                     /* LT_GT  */
  YYSYMBOL_LT_LT_EQ = 93,                  /* LT_LT_EQ  */
  YYSYMBOL_MINUS_EQ = 94,                  /* MINUS_EQ  */
  YYSYMBOL_PERCENT_EQ = 95,                /* PERCENT_EQ  */
  YYSYMBOL_PIPE_EQ = 96,                   /* PIPE_EQ  */
  YYSYMBOL_PLUS_EQ = 97,                   /* PLUS_EQ  */
  YYSYMBOL_RT_RT_EQ = 98,                  /* RT_RT_EQ  */
  YYSYMBOL_STAR_EQ = 99,                   /* STAR_EQ  */
  YYSYMBOL_INDENT = 100,                   /* INDENT  */
  YYSYMBOL_DEDENT = 101,                   /* DEDENT  */
  YYSYMBOL_ENDMARKER = 102,                /* ENDMARKER  */
  YYSYMBOL_YYACCEPT = 103,                 /* $accept  */
  YYSYMBOL_input = 104,                    /* input  */
  YYSYMBOL_stmts = 105,                    /* stmts  */
  YYSYMBOL_globalstatement = 106,          /* globalstatement  */
  YYSYMBOL_nonlocalstmt = 107,             /* nonlocalstmt  */
  YYSYMBOL_stmt = 108,                     /* stmt  */
  YYSYMBOL_normalstmt = 109,               /* normalstmt  */
  YYSYMBOL_compoundstmt = 110,             /* compoundstmt  */
  YYSYMBOL_exprstmt = 111,                 /* exprstmt  */
  YYSYMBOL_returnnstmt = 112,              /* returnnstmt  */
  YYSYMBOL_delstmt = 113,                  /* delstmt  */
  YYSYMBOL_assignstmt = 114,               /* assignstmt  */
  YYSYMBOL_assignments = 115,              /* assignments  */
  YYSYMBOL_vardeclaration = 116,           /* vardeclaration  */
  YYSYMBOL_typeDeclaration = 117,          /* typeDeclaration  */
  YYSYMBOL_ids = 118,                      /* ids  */
  YYSYMBOL_primitiveType = 119,            /* primitiveType  */
  YYSYMBOL_numericType = 120,              /* numericType  */
  YYSYMBOL_listType = 121,                 /* listType  */
  YYSYMBOL_logicalOr = 122,                /* logicalOr  */
  YYSYMBOL_logicalAnd = 123,               /* logicalAnd  */
  YYSYMBOL_bitwiseOr = 124,                /* bitwiseOr  */
  YYSYMBOL_bitwiseXor = 125,               /* bitwiseXor  */
  YYSYMBOL_bitwiseAnd = 126,               /* bitwiseAnd  */
  YYSYMBOL_listExpr = 127,                 /* listExpr  */
  YYSYMBOL_expression = 128,               /* expression  */
  YYSYMBOL_equalExpr = 129,                /* equalExpr  */
  YYSYMBOL_shiftExpr = 130,                /* shiftExpr  */
  YYSYMBOL_addExpr = 131,                  /* addExpr  */
  YYSYMBOL_relExpr = 132,                  /* relExpr  */
  YYSYMBOL_multiplicativeExpr = 133,       /* multiplicativeExpr  */
  YYSYMBOL_expoExpr = 134,                 /* expoExpr  */
  YYSYMBOL_negated_expr = 135,             /* negated_expr  */
  YYSYMBOL_primaryExpr = 136,              /* primaryExpr  */
  YYSYMBOL_arguments = 137,                /* arguments  */
  YYSYMBOL_funccall = 138,                 /* funccall  */
  YYSYMBOL_methodcall = 139,               /* methodcall  */
  YYSYMBOL_elif_action = 140,              /* elif_action  */
  YYSYMBOL_ifstatement = 141,              /* ifstatement  */
  YYSYMBOL_elifstmt = 142,                 /* elifstmt  */
  YYSYMBOL_elifstmts = 143,                /* elifstmts  */
  YYSYMBOL_elseblock = 144,                /* elseblock  */
  YYSYMBOL_forstmt = 145,                  /* forstmt  */
  YYSYMBOL_ForList = 146,                  /* ForList  */
  YYSYMBOL_loop_action = 147,              /* loop_action  */
  YYSYMBOL_whilestatement = 148,           /* whilestatement  */
  YYSYMBOL_parameters = 149,               /* parameters  */
  YYSYMBOL_returnType = 150,               /* returnType  */
  YYSYMBOL_forexpr = 151,                  /* forexpr  */
  YYSYMBOL_funcdef = 152,                  /* funcdef  */
  YYSYMBOL_funcheader = 153,               /* funcheader  */
  YYSYMBOL_classdef = 154,                 /* classdef  */
  YYSYMBOL_classheader = 155,              /* classheader  */
  YYSYMBOL_classarguments = 156,           /* classarguments  */
  YYSYMBOL_Suite = 157,                    /* Suite  */
  YYSYMBOL_ending = 158                    /* ending  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  94
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   418

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  103
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  160
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  289

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   357


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,  1764,  1764,  1774,  1785,  1794,  1807,  1821,  1834,  1842,
    1855,  1861,  1867,  1877,  1887,  1894,  1901,  1907,  1914,  1920,
    1929,  1935,  1941,  1947,  1953,  1966,  2023,  2044,  2060,  2072,
    2079,  2098,  2116,  2132,  2150,  2168,  2184,  2202,  2220,  2238,
    2256,  2274,  2292,  2313,  2334,  2357,  2382,  2395,  2411,  2438,
    2474,  2527,  2584,  2593,  2602,  2611,  2620,  2645,  2656,  2670,
    2693,  2703,  2720,  2729,  2747,  2756,  2773,  2783,  2800,  2810,
    2827,  2851,  2866,  2876,  2889,  2899,  2913,  2926,  2940,  2953,
    2966,  2984,  2995,  3008,  3024,  3034,  3047,  3063,  3073,  3086,
    3100,  3120,  3133,  3149,  3160,  3173,  3187,  3200,  3216,  3226,
    3243,  3255,  3269,  3283,  3297,  3317,  3329,  3343,  3357,  3375,
    3386,  3397,  3410,  3419,  3431,  3461,  3475,  3494,  3505,  3529,
    3543,  3604,  3655,  3672,  3680,  3715,  3746,  3773,  3793,  3822,
    3832,  3859,  3875,  3917,  3957,  3969,  3986,  4014,  4036,  4047,
    4078,  4109,  4125,  4150,  4173,  4188,  4197,  4209,  4259,  4283,
    4339,  4394,  4412,  4440,  4468,  4499,  4519,  4526,  4537,  4548,
    4555
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NEWLINE", "AS",
  "ASYNC", "ASSERT", "AWAIT", "BREAK", "CLASS", "CONTINUE", "DEF", "DEL",
  "ELIF", "ELSE", "EXCEPT", "FALSE", "FINALLY", "FOR", "FROM", "GLOBAL",
  "IF", "IMPORT", "IN", "IS", "LAMBDA", "NONE", "NONLOCAL", "PASS",
  "RAISE", "RETURN", "TRUE", "TRY", "WHILE", "WITH", "YIELD", "RANGE",
  "LEN", "PRINT", "NAME", "NUMBER", "NUMBER_INT", "NUMBER_FLOAT", "INT",
  "FLOAT", "STR", "BOOL", "LIST", "TRIPLE_DOT", "MINUS", "PLUS",
  "ASTERISK", "FORWARDSLASH", "DOUBLESLASH", "DOUBLE_STAR", "NOT", "OR",
  "AND", "LT_LT", "GT_GT", "AMPERSAND", "BAR", "CAP", "TILDE", "COLON_EQ",
  "LT", "GT", "LT_EQ", "GT_EQ", "EQ_EQ", "NOT_EQ", "PERCENT", "STRING",
  "LPAREN", "RPAREN", "LCURLY", "RCURLY", "LSQUARE", "RSQUARE", "DOT",
  "COMMA", "COLON", "SEMICOLON", "RARR", "AMPERSAND_EQ", "AT", "AT_EQ",
  "CAP_EQ", "DOUBLE_SLASH_EQ", "DOUBLE_STAR_EQ", "EQUALS",
  "FORWARDSLASH_EQ", "LT_GT", "LT_LT_EQ", "MINUS_EQ", "PERCENT_EQ",
  "PIPE_EQ", "PLUS_EQ", "RT_RT_EQ", "STAR_EQ", "INDENT", "DEDENT",
  "ENDMARKER", "$accept", "input", "stmts", "globalstatement",
  "nonlocalstmt", "stmt", "normalstmt", "compoundstmt", "exprstmt",
  "returnnstmt", "delstmt", "assignstmt", "assignments", "vardeclaration",
  "typeDeclaration", "ids", "primitiveType", "numericType", "listType",
  "logicalOr", "logicalAnd", "bitwiseOr", "bitwiseXor", "bitwiseAnd",
  "listExpr", "expression", "equalExpr", "shiftExpr", "addExpr", "relExpr",
  "multiplicativeExpr", "expoExpr", "negated_expr", "primaryExpr",
  "arguments", "funccall", "methodcall", "elif_action", "ifstatement",
  "elifstmt", "elifstmts", "elseblock", "forstmt", "ForList",
  "loop_action", "whilestatement", "parameters", "returnType", "forexpr",
  "funcdef", "funcheader", "classdef", "classheader", "classarguments",
  "Suite", "ending", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-228)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-124)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     259,     3,  -228,   -14,  -228,    30,   327,  -228,    33,    49,
     327,  -228,    57,  -228,   327,  -228,   327,   -34,   -11,   126,
    -228,  -228,   327,   327,   327,   327,  -228,   327,   327,  -228,
     107,   259,  -228,  -228,  -228,   112,  -228,  -228,  -228,  -228,
    -228,  -228,  -228,    12,   319,    84,   106,   103,   111,   114,
    -228,    96,   -12,   -39,   -48,    23,  -228,   123,  -228,  -228,
    -228,  -228,  -228,  -228,   159,  -228,   -52,  -228,  -228,  -228,
     105,   -37,  -228,  -228,   165,   121,  -228,   125,  -228,  -228,
     129,   327,   327,   327,   327,   153,   137,  -228,  -228,  -228,
    -228,   146,    78,  -228,  -228,  -228,  -228,  -228,   327,   327,
     327,   327,   327,   327,   327,   327,   327,   327,   327,   327,
     327,   327,   327,   327,   327,   327,   327,   327,   188,   327,
     181,   327,   327,   327,   327,   327,   327,   327,   327,   327,
     327,   327,   327,   327,   327,   327,   327,   327,   133,   226,
    -228,   191,   159,   195,   196,   -24,  -228,   159,  -228,   157,
     164,   168,   169,   161,   -57,  -228,  -228,  -228,  -228,  -228,
    -228,  -228,   167,  -228,  -228,  -228,  -228,  -228,   327,  -228,
    -228,  -228,  -228,  -228,  -228,  -228,   155,  -228,  -228,  -228,
    -228,  -228,  -228,  -228,  -228,  -228,   106,   103,   111,   114,
      96,   -51,  -228,   -48,   188,   -48,   -48,   -48,   -39,   -39,
      23,    23,   -12,   -12,   -12,   -12,   -12,  -228,  -228,  -228,
    -228,  -228,   307,  -228,  -228,   -17,  -228,    80,  -228,   -15,
     173,   174,   327,  -228,  -228,  -228,   159,   130,   159,   327,
    -228,  -228,  -228,  -228,   327,   209,   137,  -228,   211,  -228,
      40,   170,   213,    87,   209,   327,   113,   239,   176,   241,
    -228,   239,  -228,   185,    80,   177,  -228,  -228,   159,  -228,
    -228,    54,  -228,   180,  -228,  -228,   159,   327,  -228,   135,
    -228,  -228,  -228,  -228,  -228,  -228,   182,   327,  -228,   183,
    -228,  -228,  -228,   193,   159,   327,  -228,   200,  -228
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    12,     0,    13,     0,     0,   110,     0,     0,
       0,   111,     0,    14,    27,   109,     0,     0,     0,    49,
     106,   107,     0,     0,     0,     0,   108,     0,    72,   160,
       0,     0,    15,    16,     4,     0,     9,    10,    18,    11,
      17,    29,    25,    46,   105,    73,    60,    62,    64,    66,
      19,    68,    87,    81,    74,    84,    93,    98,   100,   112,
      20,    22,    21,    23,     0,    24,     0,     3,   159,   153,
       0,    49,   105,    28,     0,     0,     6,     0,     7,    26,
       0,   117,   117,   117,     0,     0,     0,   101,   104,   102,
     103,     0,     0,    71,     1,     5,     2,     8,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     148,   156,     0,   144,     0,     0,   138,     0,   138,   115,
       0,     0,     0,     0,    51,    48,   121,    56,    57,    58,
      53,    54,     0,    47,    52,    55,   113,   114,     0,    45,
      37,    36,    39,    34,    42,    43,   105,    44,    33,    41,
      31,    35,    38,    30,    40,    32,    61,    63,    65,    67,
      69,    49,    79,    78,     0,    77,    75,    76,    82,    83,
      86,    85,    89,    90,    91,    92,    88,    94,    95,    96,
      97,    99,     0,   157,   154,     0,   151,   143,   141,     0,
      51,     0,    72,   136,   135,   147,     0,   127,     0,   117,
     119,   118,   120,    50,   117,     0,     0,    70,     0,    80,
       0,     0,     0,     0,     0,     0,     0,   133,     0,     0,
     126,   140,   116,     0,     0,     0,    51,   158,     0,   155,
     150,     0,   142,     0,   137,   132,     0,     0,   129,   125,
     139,   122,    59,   152,   146,   145,     0,     0,   131,     0,
     130,   124,   149,     0,     0,     0,   128,     0,   134
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -228,  -228,    53,  -228,  -228,   -29,     1,  -228,  -228,  -228,
    -228,  -228,   172,  -138,   -78,     0,  -227,  -228,  -228,  -228,
     175,   179,   163,   166,    59,    27,   178,   -45,   -33,   102,
      26,    82,    99,  -228,   -79,   138,  -228,  -228,  -228,    22,
    -228,  -224,  -228,  -228,   151,  -228,  -228,  -228,  -228,  -228,
    -228,  -228,  -228,  -228,  -112,     7
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    30,    31,    32,    33,    34,   139,    36,    37,    38,
      39,    40,    41,    42,    43,    72,   163,   164,   165,    45,
      46,    47,    48,    49,    92,    50,    51,    52,    53,    54,
      55,    56,    57,    58,   150,    59,   156,   249,    60,   268,
     269,   250,    61,   225,   226,    62,   219,   276,    75,    63,
      64,    65,    66,   215,   140,    67
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      44,    35,    95,   151,   152,   218,     1,   155,    68,   255,
     126,   127,   221,    17,    18,    71,   234,   128,   129,   130,
     131,   141,   235,   265,    86,    69,    84,   270,   238,   142,
     216,    44,    35,    73,   275,   227,    83,    77,    96,    81,
      84,    79,   144,    80,   132,   281,   124,   125,     2,     3,
       4,     5,     6,   222,    91,    93,     7,   241,     8,   243,
       9,    10,    82,   242,    44,   244,    11,    12,    13,    70,
      14,    15,    74,    16,   133,   134,   135,    17,    18,    19,
     274,    20,    21,   202,   203,   204,   205,   206,    76,    22,
      23,   198,   199,   157,   136,    24,    78,   158,   159,   160,
     161,   162,    98,    25,   176,    29,   262,    94,   149,   149,
     149,   153,    26,    27,   247,    97,   251,    28,   192,   118,
     119,    87,    88,    89,    90,   169,   170,   171,   172,   173,
     174,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     113,   257,    44,  -123,   248,   223,   273,    44,   267,   248,
     252,   120,   200,   201,   278,   253,   167,   155,   168,   235,
     121,    86,   138,   114,   115,   122,   123,     2,   260,     4,
     261,     6,   286,   116,   117,     7,   157,   137,   143,     9,
     158,   159,   160,   161,   162,    11,    12,    13,   145,    14,
      15,   264,   154,   168,   239,   237,    17,    18,    19,    83,
      20,    21,   146,    84,   194,    85,   147,    86,    22,    23,
     148,    95,    44,    35,    24,   207,   208,   209,   210,   211,
     166,   193,    25,   195,   196,   197,    44,   191,    44,   213,
     214,    26,    27,   212,   217,   220,    28,   229,   230,   233,
      44,    35,   231,   232,   236,   104,   234,   245,   254,    93,
     256,   258,   259,   248,   267,   272,   149,   266,    44,   271,
     277,   149,     1,   282,   284,   240,    44,     2,     3,     4,
       5,     6,   263,   285,   288,     7,   175,     8,   188,     9,
      10,   246,   189,   224,    44,    11,    12,    13,   186,    14,
      15,   280,    16,   187,   279,   190,    17,    18,    19,   228,
      20,    21,     0,     0,   283,     0,     0,     0,    22,    23,
       0,     0,   287,     0,    24,     2,     3,     4,     5,     6,
       0,     0,    25,     7,     0,     8,     0,     9,    10,     0,
       0,    26,    27,    11,    12,    13,    28,    14,    15,     0,
      16,     0,     0,     7,    17,    18,    19,     0,    20,    21,
       0,     0,     0,    11,     0,     0,    22,    23,    15,     0,
       0,    29,    24,     0,    17,    18,    71,     0,    20,    21,
      25,     0,     0,     0,     0,     0,    22,    23,     0,    26,
      27,     0,    24,     0,    28,     0,     0,     0,     0,     0,
      25,     0,     0,     0,     0,     0,     0,     0,     0,    26,
      27,     0,     0,    99,    28,   100,   101,   102,   103,   104,
     105,     0,   106,   107,   108,   109,   110,   111,   112
};

static const yytype_int16 yycheck[] =
{
       0,     0,    31,    82,    83,   143,     3,    85,     1,   236,
      49,    50,    36,    37,    38,    39,    73,    65,    66,    67,
      68,    73,    79,   247,    81,    39,    77,   251,    79,    81,
     142,    31,    31,     6,   261,   147,    73,    10,    31,    73,
      77,    14,    79,    16,    92,   269,    58,    59,     8,     9,
      10,    11,    12,    77,    27,    28,    16,    74,    18,    74,
      20,    21,    73,    80,    64,    80,    26,    27,    28,    39,
      30,    31,    39,    33,    51,    52,    53,    37,    38,    39,
      26,    41,    42,   128,   129,   130,   131,   132,    39,    49,
      50,   124,   125,    39,    71,    55,    39,    43,    44,    45,
      46,    47,    90,    63,   104,   102,   244,     0,    81,    82,
      83,    84,    72,    73,   226,     3,   228,    77,   118,    23,
      24,    22,    23,    24,    25,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
      56,   101,   142,    13,    14,   145,   258,   147,    13,    14,
     229,    55,   126,   127,   266,   234,    78,   235,    80,    79,
      64,    81,     3,    57,    61,    69,    70,     8,    81,    10,
      83,    12,   284,    62,    60,    16,    39,    54,    73,    20,
      43,    44,    45,    46,    47,    26,    27,    28,    23,    30,
      31,    78,    39,    80,   194,   168,    37,    38,    39,    73,
      41,    42,    81,    77,    23,    79,    81,    81,    49,    50,
      81,   240,   212,   212,    55,   133,   134,   135,   136,   137,
      74,   119,    63,   121,   122,   123,   226,    39,   228,     3,
      39,    72,    73,   100,    39,    39,    77,    80,    74,    78,
     240,   240,    74,    74,    77,    90,    73,    73,    39,   222,
      39,    81,    39,    14,    13,    78,   229,    81,   258,    74,
      80,   234,     3,    81,    81,   212,   266,     8,     9,    10,
      11,    12,   245,    80,    74,    16,   104,    18,   115,    20,
      21,   222,   116,   145,   284,    26,    27,    28,   113,    30,
      31,   269,    33,   114,   267,   117,    37,    38,    39,   148,
      41,    42,    -1,    -1,   277,    -1,    -1,    -1,    49,    50,
      -1,    -1,   285,    -1,    55,     8,     9,    10,    11,    12,
      -1,    -1,    63,    16,    -1,    18,    -1,    20,    21,    -1,
      -1,    72,    73,    26,    27,    28,    77,    30,    31,    -1,
      33,    -1,    -1,    16,    37,    38,    39,    -1,    41,    42,
      -1,    -1,    -1,    26,    -1,    -1,    49,    50,    31,    -1,
      -1,   102,    55,    -1,    37,    38,    39,    -1,    41,    42,
      63,    -1,    -1,    -1,    -1,    -1,    49,    50,    -1,    72,
      73,    -1,    55,    -1,    77,    -1,    -1,    -1,    -1,    -1,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      73,    -1,    -1,    84,    77,    86,    87,    88,    89,    90,
      91,    -1,    93,    94,    95,    96,    97,    98,    99
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     8,     9,    10,    11,    12,    16,    18,    20,
      21,    26,    27,    28,    30,    31,    33,    37,    38,    39,
      41,    42,    49,    50,    55,    63,    72,    73,    77,   102,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   122,   123,   124,   125,   126,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   138,
     141,   145,   148,   152,   153,   154,   155,   158,   158,    39,
      39,    39,   118,   128,    39,   151,    39,   128,    39,   128,
     128,    73,    73,    73,    77,    79,    81,   135,   135,   135,
     135,   128,   127,   128,     0,   108,   158,     3,    90,    84,
      86,    87,    88,    89,    90,    91,    93,    94,    95,    96,
      97,    98,    99,    56,    57,    61,    62,    60,    23,    24,
      55,    64,    69,    70,    58,    59,    49,    50,    65,    66,
      67,    68,    92,    51,    52,    53,    71,    54,     3,   109,
     157,    73,    81,    73,    79,    23,    81,    81,    81,   128,
     137,   137,   137,   128,    39,   117,   139,    39,    43,    44,
      45,    46,    47,   119,   120,   121,    74,    78,    80,   128,
     128,   128,   128,   128,   128,   115,   118,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   123,   124,   125,   126,
     129,    39,   118,   132,    23,   132,   132,   132,   131,   131,
     133,   133,   130,   130,   130,   130,   130,   134,   134,   134,
     134,   134,   100,     3,    39,   156,   157,    39,   116,   149,
      39,    36,    77,   118,   138,   146,   147,   157,   147,    80,
      74,    74,    74,    78,    73,    79,    77,   128,    79,   118,
     105,    74,    80,    74,    80,    73,   127,   157,    14,   140,
     144,   157,   137,   137,    39,   119,    39,   101,    81,    39,
      81,    83,   116,   128,    78,   144,    81,    13,   142,   143,
     144,    74,    78,   157,    26,   119,   150,    80,   157,   128,
     142,   144,    81,   128,    81,    80,   157,   128,    74
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   103,   104,   104,   105,   105,   106,   107,   108,   108,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     110,   110,   110,   110,   110,   111,   112,   112,   113,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   115,   115,   116,   116,   117,   117,   118,
     118,   118,   119,   119,   119,   119,   119,   120,   120,   121,
     122,   122,   123,   123,   124,   124,   125,   125,   126,   126,
     127,   127,   127,   128,   129,   129,   129,   129,   129,   129,
     129,   130,   130,   130,   131,   131,   131,   132,   132,   132,
     132,   132,   132,   133,   133,   133,   133,   133,   134,   134,
     135,   135,   135,   135,   135,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   137,   137,   137,   138,   138,
     138,   138,   139,   140,   141,   141,   141,   141,   142,   143,
     143,   144,   145,   145,   146,   146,   146,   146,   147,   148,
     148,   149,   149,   149,   149,   150,   150,   151,   152,   153,
     153,   154,   154,   155,   156,   156,   156,   157,   157,   158,
     158
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     2,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     3,     3,     1,
       4,     3,     1,     1,     1,     1,     1,     1,     1,     4,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       3,     1,     0,     1,     1,     3,     3,     3,     3,     3,
       4,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       1,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     1,     3,     0,     4,     4,
       4,     3,     4,     0,     7,     6,     5,     4,     4,     1,
       2,     3,     6,     5,     8,     1,     1,     3,     0,     6,
       5,     1,     3,     1,     0,     1,     1,     3,     2,     8,
       6,     3,     6,     2,     1,     3,     0,     2,     4,     2,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* input: stmts ending  */
#line 1764 "parser.y"
                        {
            debugging("input", 1);
            (yyval.node).nodeNum = nodeInit("input");
            ParentToChild((yyval.node).nodeNum, (yyvsp[-1].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            (yyval.node).TAC = concat((yyvsp[-1].node).TAC, str((yyvsp[0].node).TAC));
            TAC_output = str((yyval.node).TAC);

            }
#line 3138 "parser.tab.c"
    break;

  case 3: /* input: ending  */
#line 1774 "parser.y"
                  {
            (yyval.node).nodeNum = nodeInit("input");
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            (yyval.node).TAC = (yyvsp[0].node).TAC;
            TAC_output = str((yyval.node).TAC);

        }
#line 3151 "parser.tab.c"
    break;

  case 4: /* stmts: stmt  */
#line 1785 "parser.y"
               { 
            (yyval.node).nodeNum = nodeInit("stmts");
            ParentToChild((yyval.node).nodeNum,(yyvsp[0].node).nodeNum);
            debugging("stmts", 1);

            strcpy((yyval.node).end_label, (yyvsp[0].node).end_label);
            (yyval.node).TAC = (yyvsp[0].node).TAC;

        }
#line 3165 "parser.tab.c"
    break;

  case 5: /* stmts: stmts stmt  */
#line 1794 "parser.y"
                     { 
            debugging("stmts", 1);

            (yyval.node).nodeNum = (yyvsp[-1].node).nodeNum;
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            strcpy((yyval.node).end_label, (yyvsp[0].node).end_label);
            (yyval.node).TAC = concat((yyvsp[-1].node).TAC, str((yyvsp[0].node).TAC));
        
        }
#line 3180 "parser.tab.c"
    break;

  case 6: /* globalstatement: GLOBAL NAME  */
#line 1807 "parser.y"
                       { 
            debugging("global statement", 1);
            (yyval.node).nodeNum = nodeInit("Global");
            string name = (yyvsp[0].text);
            ParentToChild((yyval.node).nodeNum, nodeInit(name));

            string code = "global" + str((yyvsp[0].text));
            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            
        }
#line 3196 "parser.tab.c"
    break;

  case 7: /* nonlocalstmt: NONLOCAL NAME  */
#line 1821 "parser.y"
                       { 
            debugging("nonlocal statement", 1);
            (yyval.node).nodeNum = nodeInit("nonlocal");
            string name = (yyvsp[0].text);
            ParentToChild((yyval.node).nodeNum, nodeInit(name));

            string code = "global" + str((yyvsp[0].text));
            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat((yyval.node).TAC, code);            
        }
#line 3211 "parser.tab.c"
    break;

  case 8: /* stmt: normalstmt NEWLINE  */
#line 1834 "parser.y"
                            {
            (yyval.node).nodeNum = (yyvsp[-1].node).nodeNum;
            debugging("stmt", 1);

            string s_end = getLabel();
            strcpy((yyval.node).end_label, s_end.c_str());
            (yyval.node).TAC = (yyvsp[-1].node).TAC;
        }
#line 3224 "parser.tab.c"
    break;

  case 9: /* stmt: compoundstmt  */
#line 1842 "parser.y"
                        { 
            debugging("stmt", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            string s_end = getLabel();
            strcpy((yyval.node).end_label, s_end.c_str());
            (yyval.node).TAC = (yyvsp[0].node).TAC;

        }
#line 3238 "parser.tab.c"
    break;

  case 10: /* normalstmt: exprstmt  */
#line 1855 "parser.y"
                     { 
            debugging("normalstmt", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            (yyval.node).TAC = (yyvsp[0].node).TAC;
        }
#line 3249 "parser.tab.c"
    break;

  case 11: /* normalstmt: delstmt  */
#line 1861 "parser.y"
                               { 
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;
            debugging("normalstmt", 1);

            (yyval.node).TAC = (yyvsp[0].node).TAC;
        }
#line 3260 "parser.tab.c"
    break;

  case 12: /* normalstmt: BREAK  */
#line 1867 "parser.y"
                          {
            debugging("normal break stmt", 1);    
            (yyval.node).nodeNum = nodeInit("break");

            (yyval.node).TAC = nullCST();
            string break_label = breakStk.top();
            string code = "goto " + break_label;
            (yyval.node).TAC = concat((yyval.node).TAC, code);       

        }
#line 3275 "parser.tab.c"
    break;

  case 13: /* normalstmt: CONTINUE  */
#line 1877 "parser.y"
                           { 
            (yyval.node).nodeNum = nodeInit("continue");            
            debugging("normal continue stmt", 1);

            (yyval.node).TAC = nullCST();
            string cont_label = contStk.top();
            string code = "goto " + cont_label;
            (yyval.node).TAC = concat((yyval.node).TAC, code); 

        }
#line 3290 "parser.tab.c"
    break;

  case 14: /* normalstmt: PASS  */
#line 1887 "parser.y"
                {
            debugging("normal pass stmt", 1);
            (yyval.node).nodeNum = nodeInit("pass");

            (yyval.node).TAC = nullCST();
            
        }
#line 3302 "parser.tab.c"
    break;

  case 15: /* normalstmt: globalstatement  */
#line 1894 "parser.y"
                                  { 
            debugging("normal global stmt", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            (yyval.node).TAC = (yyvsp[0].node).TAC;

        }
#line 3314 "parser.tab.c"
    break;

  case 16: /* normalstmt: nonlocalstmt  */
#line 1901 "parser.y"
                            { 
            debugging("normal nonlocal stmt", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            (yyval.node).TAC = (yyvsp[0].node).TAC;
        }
#line 3325 "parser.tab.c"
    break;

  case 17: /* normalstmt: assignstmt  */
#line 1907 "parser.y"
                            { 
            debugging("normal assign stmt", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            (yyval.node).TAC = (yyvsp[0].node).TAC;

        }
#line 3337 "parser.tab.c"
    break;

  case 18: /* normalstmt: returnnstmt  */
#line 1914 "parser.y"
                              { 
            debugging("normal return stmt", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            (yyval.node).TAC = (yyvsp[0].node).TAC;
        }
#line 3348 "parser.tab.c"
    break;

  case 19: /* normalstmt: expression  */
#line 1920 "parser.y"
                                     { 
            debugging("normal expression stmt", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            (yyval.node).TAC = (yyvsp[0].node).TAC;
        }
#line 3359 "parser.tab.c"
    break;

  case 20: /* compoundstmt: ifstatement  */
#line 1929 "parser.y"
                     {
            debugging("compound stmt", 1);
            (yyval.node).nodeNum=(yyvsp[0].node).nodeNum;

            (yyval.node).TAC = (yyvsp[0].node).TAC;
        }
#line 3370 "parser.tab.c"
    break;

  case 21: /* compoundstmt: whilestatement  */
#line 1935 "parser.y"
                          { 
            debugging("compound stmt", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            (yyval.node).TAC = (yyvsp[0].node).TAC;
        }
#line 3381 "parser.tab.c"
    break;

  case 22: /* compoundstmt: forstmt  */
#line 1941 "parser.y"
                   { 
            debugging("compound stmt", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            (yyval.node).TAC = (yyvsp[0].node).TAC;
        }
#line 3392 "parser.tab.c"
    break;

  case 23: /* compoundstmt: funcdef  */
#line 1947 "parser.y"
                   { 
            debugging("compound stmt", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            (yyval.node).TAC = (yyvsp[0].node).TAC;
        }
#line 3403 "parser.tab.c"
    break;

  case 24: /* compoundstmt: classdef  */
#line 1953 "parser.y"
                    { 
            debugging("compound stmt", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            (yyval.node).TAC = (yyvsp[0].node).TAC;
        }
#line 3414 "parser.tab.c"
    break;

  case 25: /* exprstmt: vardeclaration  */
#line 1966 "parser.y"
                          { 
            debugging("exprstmt", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            if((yyvsp[0].node).is_self){
                SymbolTable* classST = curr_table->Parent;
                if((classST->Table).find({(yyvsp[0].node).lexeme,""} ) != classST->Table.end()){

                    SymbolEntry* memEntry = &((classST->Table)[{(yyvsp[0].node).lexeme,""}]);
                    cout << "Member " << (yyvsp[0].node).lexeme << " already declared at line " << memEntry->lineno << endl;
                    yyerror("Variable redeclaration");
                }
                
                int temp2 = offsetStk.top();
                offsetStk.pop();
                classST->entry((yyvsp[0].node).lexeme, "", "NAME", (yyvsp[0].node).type, getSize((yyvsp[0].node).type), temp2, "class", yylineno, 0, 0);
                temp2 += getSize((yyvsp[0].node).type);
                offsetStk.push(temp2);

                (yyval.node).TAC = (yyvsp[0].node).TAC;

            }
            else{
                //entry into symbol table for variable declaration
                //vardecl has lexeme and type
                //check if already exists
                SymbolEntry* namelookup = curr_table->lookup({(yyvsp[0].node).lexeme,""});
                if(namelookup){
                    //exists
                    cout << "Variable previously declared at "<< namelookup->lineno << endl;
                    yyerror("Variable redeclaration");
                }else{
                    //new declaration
                    //params arent entried into symbol table
                    
                    //check if primitve type is list, because list size depends on list item type
                    string lt((yyvsp[0].node).type);
                    if(lt.compare(0,4,"list")!=0){
                        curr_table->entry((yyvsp[0].node).lexeme, "", "NAME", ((yyvsp[0].node)).type, getSize(((yyvsp[0].node)).type) , offset, curr_scope_name, yylineno, 0, 0);
                        offset = offset + getSize((yyvsp[0].node).type);
                    }
                    else{
                        //this is list
                        
                        curr_table->entry((yyvsp[0].node).lexeme,"", "NAME", ((yyvsp[0].node)).type, getSize((yyvsp[0].node).type) , offset, curr_scope_name, yylineno, (yyvsp[0].node).list_size , 0);
                        offset = offset + (yyvsp[0].node).size;

                    }

                    (yyval.node).TAC = (yyvsp[0].node).TAC;
                }

            }
        }
#line 3473 "parser.tab.c"
    break;

  case 26: /* returnnstmt: RETURN expression  */
#line 2023 "parser.y"
                            { 
            debugging("return statement",1);
            (yyval.node).nodeNum = nodeInit("return");
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            //check if inside function
            if(curr_scope_name != "func"){
                //return is outside 
                yyerror("return call outside of function definition");
            }

            //check type match with that of function body
            if( strcmp((yyvsp[0].node).type, curr_return_type)!=0){
                cout << "TypeError: function return type is "<< curr_return_type << " but returning " << (yyvsp[0].node).type << endl;
                yyerror("return type mismatch");
            }

            string code = "return " + str((yyvsp[0].node).res) + "\ngoto ra";
            (yyval.node).TAC = concat((yyvsp[0].node).TAC, code);

        }
#line 3499 "parser.tab.c"
    break;

  case 27: /* returnnstmt: RETURN  */
#line 2044 "parser.y"
                  { 
            debugging("return statement",1);
            (yyval.node).nodeNum = nodeInit("return");

            if(curr_scope_name != "func"){
                //return is outside 
                yyerror("TypeError: return call outside of function definition");
            }         
            //none can be returned for non "none" functions  

            string code = "goto ra";
            (yyval.node).TAC = cstar(code); 
        }
#line 3517 "parser.tab.c"
    break;

  case 28: /* delstmt: DEL expression  */
#line 2060 "parser.y"
                         { 
            debugging("delstmt", 1);
            (yyval.node).nodeNum = nodeInit("deleteStmt");
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string code = "del " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[0].node).res, code);
        }
#line 3530 "parser.tab.c"
    break;

  case 29: /* assignstmt: assignments  */
#line 2072 "parser.y"
                    {
            debugging("assignstmt",1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            strcpy((yyval.node).type, (yyvsp[0].node).type);
            (yyval.node).TAC = (yyvsp[0].node).TAC;
        }
#line 3542 "parser.tab.c"
    break;

  case 30: /* assignstmt: ids PLUS_EQ expression  */
#line 2079 "parser.y"
                                  {
            (yyval.node).nodeNum = nodeInit("+=");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            //ids is checke for declare before use
            //type check
            if(strcmp((yyvsp[-2].node).type, (yyvsp[0].node).type)!=0){
                cout << "TypeError: Type mismatch "<<  (yyvsp[-2].node).type << "and " << (yyvsp[0].node).type << endl;
                yyerror("TypeError");
            }

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + "+" + str((yyvsp[0].node).res);
            code = code + "\n" + str((yyvsp[-2].node).res) + " = " + t;
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);

        }
#line 3566 "parser.tab.c"
    break;

  case 31: /* assignstmt: ids MINUS_EQ expression  */
#line 2098 "parser.y"
                                   {
            (yyval.node).nodeNum = nodeInit("-=");
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            //type check
            if(strcmp((yyvsp[-2].node).type, (yyvsp[0].node).type)!=0){
                cout << "TypeError: Type mismatch " <<  (yyvsp[-2].node).type << "and " << (yyvsp[0].node).type << endl;
                yyerror("TypeError");
            }

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + "-" + str((yyvsp[0].node).res);
            code = code + "\n" + str((yyvsp[-2].node).res) + " = " + t;
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);

         }
#line 3589 "parser.tab.c"
    break;

  case 32: /* assignstmt: ids STAR_EQ expression  */
#line 2116 "parser.y"
                                  { 
            (yyval.node).nodeNum = nodeInit("*=");
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            //type check
            if(strcmp((yyvsp[-2].node).type, (yyvsp[0].node).type)!=0){
                cout << "TypeError: Type mismatch " << (yyvsp[-2].node).type << "and " << (yyvsp[0].node).type << endl;
                yyerror("TypeError");
            }
            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + "*" + str((yyvsp[0].node).res);
            code = code + "\n" + str((yyvsp[-2].node).res) + " = " + t;
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
        }
#line 3610 "parser.tab.c"
    break;

  case 33: /* assignstmt: ids FORWARDSLASH_EQ expression  */
#line 2132 "parser.y"
                                          {
            (yyval.node).nodeNum = nodeInit("/=");
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            //type check
            if(strcmp((yyvsp[-2].node).type, (yyvsp[0].node).type)!=0){
                cout << "TypeError: Type mismatch " << (yyvsp[-2].node).type << "and " << (yyvsp[0].node).type << endl;
                yyerror("TypeError");
            }

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + "/" + str((yyvsp[0].node).res);
            code = code + "\n" + str((yyvsp[-2].node).res) + " = " + t;
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);

         }
#line 3633 "parser.tab.c"
    break;

  case 34: /* assignstmt: ids DOUBLE_SLASH_EQ expression  */
#line 2150 "parser.y"
                                          {
            (yyval.node).nodeNum = nodeInit("//=");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            //type check
            if(strcmp((yyvsp[-2].node).type, (yyvsp[0].node).type)!=0){
                cout << "TypeError: Type mismatch " << (yyvsp[-2].node).type << "and " << (yyvsp[0].node).type << endl;
                yyerror("TypeError");
            }

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + "//" + str((yyvsp[0].node).res);
            code = code + "\n" + str((yyvsp[-2].node).res) + " = " + t;
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);

         }
#line 3656 "parser.tab.c"
    break;

  case 35: /* assignstmt: ids PERCENT_EQ expression  */
#line 2168 "parser.y"
                                     { 
            (yyval.node).nodeNum = nodeInit("%=");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            //type check
            if(strcmp((yyvsp[-2].node).type, (yyvsp[0].node).type)!=0){
                cout << "TypeError: Type mismatch " << (yyvsp[-2].node).type << "and " << (yyvsp[0].node).type << endl;
                yyerror("TypeError");
            }
            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + "%" + str((yyvsp[0].node).res);
            code = code + "\n" + str((yyvsp[-2].node).res) + " = " + t;
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
        }
#line 3677 "parser.tab.c"
    break;

  case 36: /* assignstmt: ids AT_EQ expression  */
#line 2184 "parser.y"
                                { 
            (yyval.node).nodeNum = nodeInit("@=");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            //type check
            if(strcmp((yyvsp[-2].node).type, (yyvsp[0].node).type)!=0){
                cout << "TypeError: Type mismatch " << (yyvsp[-2].node).type << "and " << (yyvsp[0].node).type << endl;
                yyerror("TypeError");
            }

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + "@" + str((yyvsp[0].node).res);
            code = code + "\n" + str((yyvsp[-2].node).res) + " = " + t;
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);

        }
#line 3700 "parser.tab.c"
    break;

  case 37: /* assignstmt: ids AMPERSAND_EQ expression  */
#line 2202 "parser.y"
                                       {
            (yyval.node).nodeNum = nodeInit("&=");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            //type check
            if(strcmp((yyvsp[-2].node).type, (yyvsp[0].node).type)!=0){
                cout << "TypeError: Type mismatch " << (yyvsp[-2].node).type << "and " << (yyvsp[0].node).type << endl;
                yyerror("TypeError");
            }

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + "&" + str((yyvsp[0].node).res);
            code = code + "\n" + str((yyvsp[-2].node).res) + " = " + t;
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);

         }
#line 3723 "parser.tab.c"
    break;

  case 38: /* assignstmt: ids PIPE_EQ expression  */
#line 2220 "parser.y"
                                  { 
            (yyval.node).nodeNum = nodeInit("|=");
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            //type check
            if(strcmp((yyvsp[-2].node).type, (yyvsp[0].node).type)!=0){
                cout << "TypeError: Type mismatch "<<  (yyvsp[-2].node).type << "and " << (yyvsp[0].node).type << endl;
                yyerror("TypeError");
            }

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + "|" + str((yyvsp[0].node).res);
            code = code + "\n" + str((yyvsp[-2].node).res) + " = " + t;
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);

        }
#line 3746 "parser.tab.c"
    break;

  case 39: /* assignstmt: ids CAP_EQ expression  */
#line 2238 "parser.y"
                                 { 
            (yyval.node).nodeNum = nodeInit("^=");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            //type check
            if(strcmp((yyvsp[-2].node).type, (yyvsp[0].node).type)!=0){
                cout << "TypeError: Type mismatch "<<  (yyvsp[-2].node).type << "and " << (yyvsp[0].node).type << endl;
                yyerror("TypeError");
            }
            
            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + "^" + str((yyvsp[0].node).res);
            code = code + "\n" + str((yyvsp[-2].node).res) + " = " + t;
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);

        }
#line 3769 "parser.tab.c"
    break;

  case 40: /* assignstmt: ids RT_RT_EQ expression  */
#line 2256 "parser.y"
                                   {
            (yyval.node).nodeNum = nodeInit(">>=");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            //type check
            if(strcmp((yyvsp[-2].node).type, (yyvsp[0].node).type)!=0){
                cout << "TypeError: Type mismatch "<<  (yyvsp[-2].node).type << "and " << (yyvsp[0].node).type << endl;
                yyerror("TypeError");
            }

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + ">>" + str((yyvsp[0].node).res);
            code = code + "\n" + str((yyvsp[-2].node).res) + " = " + t;
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);

         }
#line 3792 "parser.tab.c"
    break;

  case 41: /* assignstmt: ids LT_LT_EQ expression  */
#line 2274 "parser.y"
                                   { 
            (yyval.node).nodeNum = nodeInit("<<=");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            //type check
            if(strcmp((yyvsp[-2].node).type, (yyvsp[0].node).type)!=0){
                cout << "TypeError: Type mismatch "<<  (yyvsp[-2].node).type << "and " << (yyvsp[0].node).type << endl;
                yyerror("TypeError");
            }

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + "<<" + str((yyvsp[0].node).res);
            code = code + "\n" + str((yyvsp[-2].node).res) + " = " + t;
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);

        }
#line 3815 "parser.tab.c"
    break;

  case 42: /* assignstmt: ids DOUBLE_STAR_EQ expression  */
#line 2292 "parser.y"
                                         { 
            (yyval.node).nodeNum = nodeInit("**=");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            //type check
            if(strcmp((yyvsp[-2].node).type, (yyvsp[0].node).type)!=0){
                cout << "TypeError: Type mismatch "<<  (yyvsp[-2].node).type << "and " << (yyvsp[0].node).type << endl;
                yyerror("TypeError");
            }

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + "**" + str((yyvsp[0].node).res);
            code = code + "\n" + str((yyvsp[-2].node).res) + " = " + t;
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);

        }
#line 3838 "parser.tab.c"
    break;

  case 43: /* assignments: ids EQUALS assignments  */
#line 2313 "parser.y"
                               { 
            debugging("assignments", 1);
            (yyval.node).nodeNum = nodeInit("=");
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            //check type match
            if(strcmp((yyvsp[-2].node).type, (yyvsp[0].node).type)==0){
                //equal
                strcpy((yyval.node).type, (yyvsp[-2].node).type);

                string code = str((yyvsp[-2].node).res) + " = " + str((yyvsp[0].node).res);
                (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
                (yyval.node).TAC = concat((yyval.node).TAC,code );
            }
            else{
                cout << "TypeError: " << (yyvsp[0].node).type << " assigned to " << (yyvsp[-2].node).type << endl;
                yyerror("Type mismatch during assignment");
            }

        }
#line 3864 "parser.tab.c"
    break;

  case 44: /* assignments: ids EQUALS expression  */
#line 2334 "parser.y"
                                 {
            debugging("assignments", 1);
            (yyval.node).nodeNum = nodeInit("=");
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            //check if type of expression matches type of ids
            if(strcmp((yyvsp[-2].node).type, (yyvsp[0].node).type)==0){
                strcpy((yyval.node).type, (yyvsp[-2].node).type);

                string code = str((yyvsp[-2].node).res) + " = " + str((yyvsp[0].node).res);
                (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
                (yyval.node).TAC = concat((yyval.node).TAC, code);
            }
            else{
                cout << "TypeError: "<< (yyvsp[0].node).type << " assigned to " << (yyvsp[-2].node).type << endl;
                yyerror("Type mismatch during assignment");
            }
         }
#line 3888 "parser.tab.c"
    break;

  case 45: /* vardeclaration: typeDeclaration EQUALS expression  */
#line 2357 "parser.y"
                                          { 
            debugging("variable declaration", 1);
            (yyval.node).nodeNum = nodeInit("=");
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            //check if var isnt already declared: DONE at typedeclaration

            //check type match
            if(strcmp((yyvsp[-2].node).type, (yyvsp[0].node).type)!=0){
                //doesn't match
                cout << "TypeError: "<< (yyvsp[0].node).type << " assigned to " << (yyvsp[-2].node).type << endl;
                yyerror("Type mismatch during assignment");
            }

            (yyval.node).is_self = (yyvsp[-2].node).is_self; 
            (yyval.node).list_size = (yyvsp[0].node).list_size;

            strcpy((yyval.node).lexeme, (yyvsp[-2].node).lexeme);
            strcpy((yyval.node).type, (yyvsp[-2].node).type);

            string code = str((yyvsp[-2].node).res) + " = " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[0].node).TAC, code);

        }
#line 3918 "parser.tab.c"
    break;

  case 46: /* vardeclaration: typeDeclaration  */
#line 2382 "parser.y"
                          {
            debugging("variable declaration", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            (yyval.node) = (yyvsp[0].node);

            strcpy((yyval.node).res, (yyvsp[0].node).res);
            (yyval.node).TAC = (yyvsp[0].node).TAC;
        }
#line 3932 "parser.tab.c"
    break;

  case 47: /* typeDeclaration: NAME COLON primitiveType  */
#line 2395 "parser.y"
                                  {
            (yyval.node).nodeNum = nodeInit(":");
            debugging("type declaration", 1);
            string t= (yyvsp[-2].text);
            string s = "ID(" +t + ")";
            ParentToChild((yyval.node).nodeNum, nodeInit(s));
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            strcpy((yyval.node).type, (yyvsp[0].node).type);
            strcpy((yyval.node).lexeme, (yyvsp[-2].text)); //IMP for parameters

            strcpy((yyval.node).res, (yyvsp[-2].text));
            (yyval.node).TAC = (yyvsp[0].node).TAC;
            
        }
#line 3952 "parser.tab.c"
    break;

  case 48: /* typeDeclaration: NAME DOT typeDeclaration  */
#line 2411 "parser.y"
                                   { 
            (yyval.node).nodeNum = nodeInit("atomicExpe");
            debugging("type declaration", 1);
            string t= (yyvsp[-2].text);
            string s = "ID(" +t + ")";
            ParentToChild((yyval.node).nodeNum, nodeInit(s));            
            int dot = nodeInit(".");            
            ParentToChild((yyval.node).nodeNum, dot);
            ParentToChild(dot, (yyvsp[0].node).nodeNum);

            //if NAME is self, declare $3.lexeme into class symbol table
            if( t != "self"){
                cout << "NAME is" << t << "|"<<endl;
                cout << (yyvsp[-2].text) << " cannot declare its member. only <self> can "<< endl;
                yyerror("Illegal declaration");
            }
            
            //NAME has to be self
            (yyval.node).is_self = 1;
            strcpy((yyval.node).lexeme, (yyvsp[0].node).lexeme);
            strcpy((yyval.node).type, (yyvsp[0].node).type);

            //TODO
        }
#line 3981 "parser.tab.c"
    break;

  case 49: /* ids: NAME  */
#line 2438 "parser.y"
            {
            debugging("ids", 1);
            string t= (yyvsp[0].text);
            string s = "ID(" +t + ")"; 
            (yyval.node).nodeNum = nodeInit(s);

            //if predefined variables don't err
            if(strcmp((yyvsp[0].text),"__name__")==0){

                strcpy((yyval.node).lexeme, (yyvsp[0].text));
                (yyval.node).TAC = nullCST();
                (yyval.node).TAC = concat((yyval.node).TAC, "@program start :");
                strcpy((yyval.node).res, (yyvsp[0].text));
            }
            else{
                // this name is being used (after declaration)
                SymbolEntry* namelookup = curr_table->lookup({(yyvsp[0].text),""});
                if(namelookup){
                    //exists: OK
                    strcpy((yyval.node).type, namelookup->type.c_str());
                    strcpy((yyval.node).lexeme, (yyvsp[0].text));

                    strcpy((yyval.node).res, (yyvsp[0].text));
                    (yyval.node).TAC = nullCST();
                }
                else{
                    //does not exits
                    // cout << "here\n";
                    yyerror("Variable not declared yet");
                }

            }

            
            
         }
#line 4022 "parser.tab.c"
    break;

  case 50: /* ids: NAME LSQUARE expression RSQUARE  */
#line 2474 "parser.y"
                                          {
            debugging("ids", 1);
            (yyval.node).nodeNum = nodeInit("atom_expr");
            string t= (yyvsp[-3].text);
            string s = "ID(" +t + ")"; 
            ParentToChild((yyval.node).nodeNum, nodeInit(s));
            int child= nodeInit("[]");
            ParentToChild((yyval.node).nodeNum, child);
            ParentToChild(child, (yyvsp[-1].node).nodeNum);

            SymbolEntry* namelookup = curr_table->lookup({(yyvsp[-3].text),""});
            if(namelookup){
                //exists: OK
                //check if list type
                if( namelookup->type.compare(0,4, "list")!=0){
                    cout << "TypeError: " << (yyvsp[-3].text) << " cannot be indexed." << endl;
                    yyerror(" Not of type <list>");
                }

                if(strcmp((yyvsp[-1].node).type, "int")!=0){
                    //accessing without int index
                    yyerror("Index must be <int> value");
                }

                //set ids type
                char ids_type[100];
                int y = 0;
                for(int x = 5; x < (namelookup->type).size()-1 ; x++){
                    ids_type[y] = (namelookup->type)[x];
                    y++;
                }
                ids_type[y] = '\0';

                string ls((yyvsp[-3].text));
                ls = ls + "[]";
                strcpy((yyval.node).type, ids_type);
                strcpy((yyval.node).lexeme, ls.c_str());

                string t = getTemp();
                string code = t + " = "  + str((yyvsp[-1].node).res) + "*" + to_string(getSize((yyval.node).type));
                string r = str((yyvsp[-3].text)) + "[" + t + "]";
                
                strcpy((yyval.node).res, r.c_str());

                (yyval.node).TAC = concat((yyvsp[-1].node).TAC, code);


            }
            else{
                yyerror("Variable not declared");
            }

        }
#line 4080 "parser.tab.c"
    break;

  case 51: /* ids: NAME DOT NAME  */
#line 2527 "parser.y"
                        {
            debugging("ids", 1);
            (yyval.node).nodeNum = nodeInit("atomic_expr");
            string t= (yyvsp[-2].text);
            string s = "ID(" +t + ")";
            ParentToChild((yyval.node).nodeNum, nodeInit(s));
            int dot = nodeInit(".");            
            ParentToChild((yyval.node).nodeNum, dot);
            ParentToChild(dot, nodeInit((yyvsp[0].text)));

            
            //check if NAME2 is defined field in NAME1 class

            //case 1: object is doing stuff with member
            //case 2: self or class name inside class funcdef is using

            SymbolEntry* nEntry = curr_table->lookup({(yyvsp[-2].text),""});
            if(nEntry){
                SymbolEntry* classN = curr_table->lookup({nEntry->type,""});
                if(!classN || classN->type!="class"){
                    cout<< (yyvsp[-2].text) << " is not object of some class" << endl;
                    yyerror("Variable cannot invoke member");
                }
                //NAME1 is object of class now
                //find class table and see if this field exists
                SymbolTable* classT = findTable(nEntry->type, "");
                auto findMem = (classT->Table).find({(yyvsp[0].text),""});
                if(findMem == (classT->Table).end()){
                    //no such field
                    cout << (yyvsp[0].text) << " is not member of class "<< nEntry->type << endl;
                    yyerror("Invalid member invoked");
                }
                auto memToken = (findMem->second).token;
                if(memToken!="NAME"){
                    cout << (yyvsp[0].text) << " is not member of class "<< nEntry->type << endl;
                    yyerror("Invalid member invoked");
                }
                //ALLGOOD
                auto memType = (findMem->second).type;
                strcpy((yyval.node).type, memType.c_str());

                //TODO


            }
            else{
                // cout << "here \n";
                cout << "Unknown variable " << (yyvsp[-2].text) << endl;
                yyerror("Unknown Variable. Must declare before use.");
            }


        }
#line 4138 "parser.tab.c"
    break;

  case 52: /* primitiveType: numericType  */
#line 2584 "parser.y"
                      { 
            debugging("primitive numeric", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            strcpy((yyval.node).type, (yyvsp[0].node).type);
            (yyval.node).size = (yyvsp[0].node).size;

            (yyval.node).TAC = (yyvsp[0].node).TAC;
        }
#line 4152 "parser.tab.c"
    break;

  case 53: /* primitiveType: STR  */
#line 2593 "parser.y"
                  { 
            debugging("primitive string", 1);
            (yyval.node).nodeNum = nodeInit("string");

            strcpy((yyval.node).type, "str");

            (yyval.node).TAC = nullCST();
            
        }
#line 4166 "parser.tab.c"
    break;

  case 54: /* primitiveType: BOOL  */
#line 2602 "parser.y"
                  {
            debugging("primitive boolean", 1);
            (yyval.node).nodeNum = nodeInit("bool"); 

            strcpy((yyval.node).type, "bool");
            (yyval.node).size = getSize("bool");

            (yyval.node).TAC = nullCST();
        }
#line 4180 "parser.tab.c"
    break;

  case 55: /* primitiveType: listType  */
#line 2611 "parser.y"
                     {
            debugging("primitive list", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            strcpy((yyval.node).type, (yyvsp[0].node).type);
            (yyval.node).size = (yyvsp[0].node).size;

            (yyval.node).TAC = (yyvsp[0].node).TAC;
        }
#line 4194 "parser.tab.c"
    break;

  case 56: /* primitiveType: NAME  */
#line 2620 "parser.y"
                     {
            debugging("primitive ids", 1);
            string t= (yyvsp[0].text);
            string s = "ID(" +t + ")";
            (yyval.node).nodeNum = nodeInit(s);
            
            //check if its a class
            SymbolEntry* classEntry = curr_table->lookup({(yyvsp[0].text),""});
            if(!classEntry){
                yyerror("TypeError: Unknown Type");
            }
            else{
                if(classEntry->token != "CLASS"){
                    yyerror("TypeError: Unknown Type");
                }

                strcpy((yyval.node).type, (yyvsp[0].text));            

                (yyval.node).TAC = nullCST();
            }
        }
#line 4220 "parser.tab.c"
    break;

  case 57: /* numericType: INT  */
#line 2645 "parser.y"
                  { 
            debugging("numeric int", 1);
            (yyval.node).nodeNum = nodeInit("int");

            // $$.type = "int"
            strcpy((yyval.node).type, "int");
            (yyval.node).size = getSize("int");

            (yyval.node).TAC = nullCST();
            
        }
#line 4236 "parser.tab.c"
    break;

  case 58: /* numericType: FLOAT  */
#line 2656 "parser.y"
                  {
            debugging("numeric float", 1);
            (yyval.node).nodeNum = nodeInit("float");

            // $$.type = "float";
            strcpy((yyval.node).type, "float");
            (yyval.node).size = getSize("float");

            (yyval.node).TAC = nullCST();
        }
#line 4251 "parser.tab.c"
    break;

  case 59: /* listType: LIST LSQUARE primitiveType RSQUARE  */
#line 2670 "parser.y"
                                           { 
            debugging("list type", 1);
            (yyval.node).nodeNum = nodeInit("atomExpr");
            ParentToChild((yyval.node).nodeNum, nodeInit("list"));
            int child = nodeInit("[]");
            ParentToChild(child, (yyvsp[-1].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, child);

            string temp((yyvsp[-1].node).type);
            string ltype = "list[" + temp + "]";
            strcpy((yyval.node).type, ltype.c_str());    
            
            (yyval.node).size = getSize(ltype);

            (yyval.node).TAC = (yyvsp[-1].node).TAC;
        }
#line 4272 "parser.tab.c"
    break;

  case 60: /* logicalOr: logicalAnd  */
#line 2693 "parser.y"
                        {
            debugging("logical or", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;
            strcpy((yyval.node).type, (yyvsp[0].node).type);

            (yyval.node).list_size = (yyvsp[0].node).list_size;

            (yyval.node).TAC = (yyvsp[0].node).TAC;
            strcpy((yyval.node).res, (yyvsp[0].node).res);
        }
#line 4287 "parser.tab.c"
    break;

  case 61: /* logicalOr: logicalOr OR logicalAnd  */
#line 2703 "parser.y"
                                  { 
            debugging("logical or", 1);
            (yyval.node).nodeNum = nodeInit("or");
            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " or " + str((yyvsp[0].node).res);
            (yyval.node).TAC = (yyvsp[-2].node).TAC;
            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
        }
#line 4306 "parser.tab.c"
    break;

  case 62: /* logicalAnd: bitwiseOr  */
#line 2720 "parser.y"
                     { 
            debugging("logical and", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            (yyval.node).list_size = (yyvsp[0].node).list_size;
            strcpy((yyval.node).type, (yyvsp[0].node).type);
            (yyval.node).TAC = (yyvsp[0].node).TAC;
            strcpy((yyval.node).res, (yyvsp[0].node).res);
        }
#line 4320 "parser.tab.c"
    break;

  case 63: /* logicalAnd: logicalAnd AND bitwiseOr  */
#line 2729 "parser.y"
                                   { 
            debugging("logical and", 1);
            (yyval.node).nodeNum= nodeInit("and");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t= getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " and " + str((yyvsp[0].node).res);
            (yyval.node).TAC = (yyvsp[-2].node).TAC;
            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
        }
#line 4338 "parser.tab.c"
    break;

  case 64: /* bitwiseOr: bitwiseXor  */
#line 2747 "parser.y"
                       { 
            debugging("bitwise or", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            (yyval.node).list_size = (yyvsp[0].node).list_size;
            strcpy((yyval.node).type, (yyvsp[0].node).type);
            (yyval.node).TAC = (yyvsp[0].node).TAC;
            strcpy((yyval.node).res, (yyvsp[0].node).res);
        }
#line 4352 "parser.tab.c"
    break;

  case 65: /* bitwiseOr: bitwiseOr BAR bitwiseXor  */
#line 2756 "parser.y"
                                   { 
            debugging("bitwise or", 1);
            (yyval.node).nodeNum = nodeInit("|");
            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t= getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " | " + str((yyvsp[0].node).res);
            (yyval.node).TAC = (yyvsp[-2].node).TAC;
            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
        }
#line 4371 "parser.tab.c"
    break;

  case 66: /* bitwiseXor: bitwiseAnd  */
#line 2773 "parser.y"
                       { 
            debugging("bitwise xor", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            (yyval.node).list_size = (yyvsp[0].node).list_size;

            strcpy((yyval.node).type, (yyvsp[0].node).type);
            (yyval.node).TAC = (yyvsp[0].node).TAC;
            strcpy((yyval.node).res, (yyvsp[0].node).res);
        }
#line 4386 "parser.tab.c"
    break;

  case 67: /* bitwiseXor: bitwiseXor CAP bitwiseAnd  */
#line 2783 "parser.y"
                                    { 
            debugging("bitwise xor", 1);
            (yyval.node).nodeNum = nodeInit("^");
            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " ^ " + str((yyvsp[0].node).res);
            (yyval.node).TAC = (yyvsp[-2].node).TAC;
            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
        }
#line 4405 "parser.tab.c"
    break;

  case 68: /* bitwiseAnd: equalExpr  */
#line 2800 "parser.y"
                       { 
            debugging("bitwise and", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            strcpy((yyval.node).type, (yyvsp[0].node).type);
            (yyval.node).list_size = (yyvsp[0].node).list_size;

            (yyval.node).TAC = (yyvsp[0].node).TAC;
            strcpy((yyval.node).res, (yyvsp[0].node).res);
        }
#line 4420 "parser.tab.c"
    break;

  case 69: /* bitwiseAnd: bitwiseAnd AMPERSAND equalExpr  */
#line 2810 "parser.y"
                                         { 
            debugging("bitwise and", 1);
            (yyval.node).nodeNum = nodeInit("&");
            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " +  str((yyvsp[-2].node).res) + " & " + str((yyvsp[0].node).res);
            (yyval.node).TAC = (yyvsp[-2].node).TAC;
            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
        }
#line 4439 "parser.tab.c"
    break;

  case 70: /* listExpr: listExpr COMMA expression  */
#line 2827 "parser.y"
                                   { 
            debugging("list expression", 1);
            (yyval.node).nodeNum = nodeInit(",");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            if(strcmp((yyvsp[-2].node).type, (yyvsp[0].node).type)!=0){
                cout << "TypeError: " << endl;
                yyerror("list of poly type not allowed");
            }

            strcpy((yyval.node).type, (yyvsp[-2].node).type);

            (yyval.node).list_size = (yyvsp[-2].node).list_size + 1;

            string list_temp = str((yyvsp[-2].node).res);
            string code = list_temp + "[" + to_string(((yyval.node).list_size-1)*getSize((yyvsp[-2].node).type)) + "]" + " = " + str((yyvsp[0].node).res);
            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat((yyval.node).TAC, (yyvsp[-2].node).TAC);
            (yyval.node).TAC = concat((yyval.node).TAC, (yyvsp[0].node).TAC);
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, list_temp.c_str());

        }
#line 4468 "parser.tab.c"
    break;

  case 71: /* listExpr: expression  */
#line 2851 "parser.y"
                     { 
            debugging("list expression", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            strcpy((yyval.node).type, (yyvsp[0].node).type);

            (yyval.node).list_size = 1;

            string list_temp = getTemp();
            string code = list_temp + "[" + to_string(((yyval.node).list_size-1)*getSize((yyvsp[0].node).type)) + "]" + " = " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[0].node).TAC, code);
            strcpy((yyval.node).res, list_temp.c_str());


        }
#line 4488 "parser.tab.c"
    break;

  case 72: /* listExpr: %empty  */
#line 2866 "parser.y"
            {
            (yyval.node).nodeNum = -1;
            (yyval.node).list_size = 0;
            (yyval.node).TAC = nullCST();
            string s = "";
            strcpy((yyval.node).res, s.c_str() );
        }
#line 4500 "parser.tab.c"
    break;

  case 73: /* expression: logicalOr  */
#line 2876 "parser.y"
                    { 
            debugging("expression", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            strcpy((yyval.node).type, (yyvsp[0].node).type);
            (yyval.node).list_size = (yyvsp[0].node).list_size;

            (yyval.node).TAC = (yyvsp[0].node).TAC;
            strcpy((yyval.node).res, (yyvsp[0].node).res);
        }
#line 4515 "parser.tab.c"
    break;

  case 74: /* equalExpr: relExpr  */
#line 2889 "parser.y"
                   { 
            debugging("equality expression", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            strcpy((yyval.node).type, (yyvsp[0].node).type);
            (yyval.node).list_size = (yyvsp[0].node).list_size;

            (yyval.node).TAC = (yyvsp[0].node).TAC;
            strcpy((yyval.node).res, (yyvsp[0].node).res);
        }
#line 4530 "parser.tab.c"
    break;

  case 75: /* equalExpr: equalExpr EQ_EQ relExpr  */
#line 2899 "parser.y"
                                  {  
            debugging("equality expression", 1);
            (yyval.node).nodeNum = nodeInit("==");
            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " == " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
            
        }
#line 4549 "parser.tab.c"
    break;

  case 76: /* equalExpr: equalExpr NOT_EQ relExpr  */
#line 2913 "parser.y"
                                   {
            debugging("equality expression", 1);
            (yyval.node).nodeNum = nodeInit("!=");
            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " != " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
        }
#line 4567 "parser.tab.c"
    break;

  case 77: /* equalExpr: equalExpr COLON_EQ relExpr  */
#line 2926 "parser.y"
                                     {
            debugging("equality expression", 1);
            (yyval.node).nodeNum = nodeInit(":=");
            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " := " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());

        }
#line 4586 "parser.tab.c"
    break;

  case 78: /* equalExpr: equalExpr IS relExpr  */
#line 2940 "parser.y"
                               {
            debugging("equality expression", 1);
            (yyval.node).nodeNum = nodeInit("=");
            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " is " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
        }
#line 4604 "parser.tab.c"
    break;

  case 79: /* equalExpr: equalExpr IN ids  */
#line 2953 "parser.y"
                           {
            debugging("equality expression", 1);
            (yyval.node).nodeNum = nodeInit("in");
            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " in " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
        }
#line 4622 "parser.tab.c"
    break;

  case 80: /* equalExpr: equalExpr NOT IN ids  */
#line 2966 "parser.y"
                               {
            debugging("equality expression", 1);
            (yyval.node).nodeNum = nodeInit("!=");
            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-3].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-3].node).res) + " not in " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[-3].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
        }
#line 4640 "parser.tab.c"
    break;

  case 81: /* shiftExpr: addExpr  */
#line 2984 "parser.y"
                  {
                    (yyval.node).nodeNum = (yyvsp[0].node).nodeNum; 
                    debugging("shift expression", 1); 

                    strcpy((yyval.node).type, (yyvsp[0].node).type); 
                    (yyval.node).list_size = (yyvsp[0].node).list_size; 

                    (yyval.node).TAC = (yyvsp[0].node).TAC;
                    strcpy((yyval.node).res, (yyvsp[0].node).res);

                }
#line 4656 "parser.tab.c"
    break;

  case 82: /* shiftExpr: shiftExpr LT_LT addExpr  */
#line 2995 "parser.y"
                                  {
            debugging("shift expression", 1);
            (yyval.node).nodeNum = nodeInit("<<");
            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " << " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
         }
#line 4674 "parser.tab.c"
    break;

  case 83: /* shiftExpr: shiftExpr GT_GT addExpr  */
#line 3008 "parser.y"
                                  { 
            debugging("shift expression", 1);
            (yyval.node).nodeNum = nodeInit(">>");
            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " >> " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
        }
#line 4692 "parser.tab.c"
    break;

  case 84: /* addExpr: multiplicativeExpr  */
#line 3024 "parser.y"
                              { 
            debugging("additive expression", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            strcpy((yyval.node).type, (yyvsp[0].node).type);
            (yyval.node).list_size = (yyvsp[0].node).list_size;

            (yyval.node).TAC = (yyvsp[0].node).TAC;
            strcpy((yyval.node).res, (yyvsp[0].node).res);
        }
#line 4707 "parser.tab.c"
    break;

  case 85: /* addExpr: addExpr PLUS multiplicativeExpr  */
#line 3034 "parser.y"
                                          { 
            debugging("additive expression", 1);
            (yyval.node).nodeNum = nodeInit("+");
            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " + " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
        }
#line 4725 "parser.tab.c"
    break;

  case 86: /* addExpr: addExpr MINUS multiplicativeExpr  */
#line 3047 "parser.y"
                                           { 
            debugging("additive expression", 1);
            (yyval.node).nodeNum = nodeInit("-");
            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " - " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
        }
#line 4743 "parser.tab.c"
    break;

  case 87: /* relExpr: shiftExpr  */
#line 3063 "parser.y"
                     { 
            debugging("relational expression", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            strcpy((yyval.node).type, (yyvsp[0].node).type);
            (yyval.node).list_size = (yyvsp[0].node).list_size;

            (yyval.node).TAC = (yyvsp[0].node).TAC;
            strcpy((yyval.node).res, (yyvsp[0].node).res);
        }
#line 4758 "parser.tab.c"
    break;

  case 88: /* relExpr: relExpr LT_GT shiftExpr  */
#line 3073 "parser.y"
                                  { 
            debugging("relational expression", 1);
            (yyval.node).nodeNum = nodeInit("<>");
            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " <> " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
        }
#line 4776 "parser.tab.c"
    break;

  case 89: /* relExpr: relExpr LT shiftExpr  */
#line 3086 "parser.y"
                               { 
            debugging("relational expression", 1);
            (yyval.node).nodeNum = nodeInit("<");
            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " < " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
        }
#line 4794 "parser.tab.c"
    break;

  case 90: /* relExpr: relExpr GT shiftExpr  */
#line 3100 "parser.y"
                               { 
            debugging("relational expression", 1);
            (yyval.node).nodeNum = nodeInit(">");
            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            // cout << "here" << endl;
        
            string t = getTemp();
            
            string code = t + " = " + str((yyvsp[-2].node).res) + " > " + str((yyvsp[0].node).res);
        
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            
            strcpy((yyval.node).res, t.c_str());

        }
#line 4819 "parser.tab.c"
    break;

  case 91: /* relExpr: relExpr LT_EQ shiftExpr  */
#line 3120 "parser.y"
                                  {
            debugging("relational expression", 1);
            (yyval.node).nodeNum = nodeInit("<=");
            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " <= " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
         }
#line 4837 "parser.tab.c"
    break;

  case 92: /* relExpr: relExpr GT_EQ shiftExpr  */
#line 3133 "parser.y"
                                  {
            debugging("relational expression", 1);
            (yyval.node).nodeNum = nodeInit(">=");
            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " >= " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
         }
#line 4855 "parser.tab.c"
    break;

  case 93: /* multiplicativeExpr: expoExpr  */
#line 3149 "parser.y"
                     { 
            debugging("multiplicative expression", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            strcpy((yyval.node).type, (yyvsp[0].node).type);
            (yyval.node).list_size = (yyvsp[0].node).list_size;

            (yyval.node).TAC = (yyvsp[0].node).TAC;
            strcpy((yyval.node).res, (yyvsp[0].node).res);

        }
#line 4871 "parser.tab.c"
    break;

  case 94: /* multiplicativeExpr: multiplicativeExpr ASTERISK expoExpr  */
#line 3160 "parser.y"
                                               { 
            debugging("multiplicative expression", 1);
            (yyval.node).nodeNum = nodeInit("*");
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " * " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
            
        }
#line 4889 "parser.tab.c"
    break;

  case 95: /* multiplicativeExpr: multiplicativeExpr FORWARDSLASH expoExpr  */
#line 3173 "parser.y"
                                                    {
            debugging("multiplicative expression", 1);
            (yyval.node).nodeNum = nodeInit("/");
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " / " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());

        
         }
#line 4908 "parser.tab.c"
    break;

  case 96: /* multiplicativeExpr: multiplicativeExpr DOUBLESLASH expoExpr  */
#line 3187 "parser.y"
                                                  {
            debugging("multiplicative expression", 1);
            (yyval.node).nodeNum = nodeInit("//");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " // " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());

         }
#line 4926 "parser.tab.c"
    break;

  case 97: /* multiplicativeExpr: multiplicativeExpr PERCENT expoExpr  */
#line 3200 "parser.y"
                                              { 
            debugging("multiplicative expression", 1);
            (yyval.node).nodeNum = nodeInit("%");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " % " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());

        }
#line 4944 "parser.tab.c"
    break;

  case 98: /* expoExpr: negated_expr  */
#line 3216 "parser.y"
                           {
            debugging("exponentiation expression", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            strcpy((yyval.node).type, (yyvsp[0].node).type);

            (yyval.node).TAC = (yyvsp[0].node).TAC;
            strcpy((yyval.node).res, (yyvsp[0].node).res);
            (yyval.node).list_size = (yyvsp[0].node).list_size;
         }
#line 4959 "parser.tab.c"
    break;

  case 99: /* expoExpr: negated_expr DOUBLE_STAR expoExpr  */
#line 3226 "parser.y"
                                            {
            debugging("exponentiation expression", 1);
            (yyval.node).nodeNum = nodeInit("**");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            strcpy((yyval.node).type, (yyvsp[-2].node).type);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-2].node).res) + " ** " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[-2].node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
         }
#line 4978 "parser.tab.c"
    break;

  case 100: /* negated_expr: primaryExpr  */
#line 3243 "parser.y"
                         {
            debugging("negated expression", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            strcpy((yyval.node).type, (yyvsp[0].node).type);

            (yyval.node).TAC = (yyvsp[0].node).TAC;
            strcpy((yyval.node).res, (yyvsp[0].node).res);

            (yyval.node).list_size = (yyvsp[0].node).list_size;
            
        }
#line 4995 "parser.tab.c"
    break;

  case 101: /* negated_expr: MINUS negated_expr  */
#line 3255 "parser.y"
                             {
            debugging("negated expression", 1);
            (yyval.node).nodeNum = nodeInit("-");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            strcpy((yyval.node).type, (yyvsp[0].node).type);

            string t = getTemp();
            string code = t + " = " + " - " + str((yyvsp[0].node).res);
            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat( (yyval.node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
         }
#line 5014 "parser.tab.c"
    break;

  case 102: /* negated_expr: NOT negated_expr  */
#line 3269 "parser.y"
                           { 
            debugging("negated expression", 1);
            (yyval.node).nodeNum = nodeInit("not");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            strcpy((yyval.node).type, (yyvsp[0].node).type);

            string t = getTemp();
            string code = t + " = " + " not " + str((yyvsp[0].node).res);
            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat( (yyval.node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
        }
#line 5033 "parser.tab.c"
    break;

  case 103: /* negated_expr: TILDE negated_expr  */
#line 3283 "parser.y"
                             {
            debugging("negated expression", 1);
            (yyval.node).nodeNum = nodeInit("~");
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            strcpy((yyval.node).type, (yyvsp[0].node).type);

            string t = getTemp();
            string code = t + " = " + " ~ " + str((yyvsp[0].node).res);
            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat( (yyval.node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
         }
#line 5052 "parser.tab.c"
    break;

  case 104: /* negated_expr: PLUS negated_expr  */
#line 3297 "parser.y"
                            { 
            debugging("negated expression", 1);
            (yyval.node).nodeNum = nodeInit("+");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            strcpy((yyval.node).type, (yyvsp[0].node).type);

            string t = getTemp();
            string code = t + " = " + " + " + str((yyvsp[0].node).res);
            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat( (yyval.node).TAC, str((yyvsp[0].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            strcpy((yyval.node).res, t.c_str());
        }
#line 5071 "parser.tab.c"
    break;

  case 105: /* primaryExpr: ids  */
#line 3317 "parser.y"
              { 
            debugging("primary expression", 1);
            // cout << "primary expression" << endl;
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            strcpy((yyval.node).type, (yyvsp[0].node).type);
            strcpy((yyval.node).lexeme, (yyvsp[0].node).lexeme);

            (yyval.node).TAC = (yyvsp[0].node).TAC;
            strcpy((yyval.node).res, (yyvsp[0].node).res);

        }
#line 5088 "parser.tab.c"
    break;

  case 106: /* primaryExpr: NUMBER_INT  */
#line 3329 "parser.y"
                     { 
            debugging("primary expression", 1);
            string t= (yyvsp[0].text);
            string s = "INT(" +t + ")"; 
            (yyval.node).nodeNum = nodeInit(s);

            strcpy((yyval.node).lexeme, (yyvsp[0].text));
            strcpy((yyval.node).type, "int");
            (yyval.node).size = getSize("int");

            (yyval.node).TAC = nullCST();
            strcpy((yyval.node).res, (yyvsp[0].text) );
            
        }
#line 5107 "parser.tab.c"
    break;

  case 107: /* primaryExpr: NUMBER_FLOAT  */
#line 3343 "parser.y"
                       { 
            debugging("primary expression", 1);
            string t= (yyvsp[0].text);
            string s = "FLOAT(" +t + ")"; 
            (yyval.node).nodeNum = nodeInit(s);

            strcpy((yyval.node).lexeme, (yyvsp[0].text));
            strcpy((yyval.node).type, "float");
            (yyval.node).size = getSize("float");

            (yyval.node).TAC = nullCST();
            strcpy((yyval.node).res, (yyvsp[0].text) );
            
        }
#line 5126 "parser.tab.c"
    break;

  case 108: /* primaryExpr: STRING  */
#line 3357 "parser.y"
                 { 
            debugging("primary expression, string", 1);
            string t= (yyvsp[0].text);
            t = t.substr(1, t.size()-2);
            t = "\\\"" + t + "\\\"";
            string s = "LITERAL(" +t + ")";
            (yyval.node).nodeNum = nodeInit(s);


            int strlen = t.size();
            (yyval.node).size = strlen*getSize("str");
            strcpy((yyval.node).lexeme, (yyvsp[0].text));
            strcpy((yyval.node).type, "str");

            (yyval.node).TAC = nullCST();
            strcpy((yyval.node).res, (yyvsp[0].text) );
            
        }
#line 5149 "parser.tab.c"
    break;

  case 109: /* primaryExpr: TRUE  */
#line 3375 "parser.y"
               {
            debugging("primary expression, true", 1);
            (yyval.node).nodeNum = nodeInit("True");

            strcpy((yyval.node).type, "bool");
            (yyval.node).size = getSize("bool");
            strcpy((yyval.node).lexeme, "true");  

            (yyval.node).TAC = nullCST();
            strcpy((yyval.node).res, (yyval.node).lexeme );          
         }
#line 5165 "parser.tab.c"
    break;

  case 110: /* primaryExpr: FALSE  */
#line 3386 "parser.y"
                {
            debugging("primary expression, false", 1);
            (yyval.node).nodeNum = nodeInit("False");
            
            strcpy((yyval.node).type, "bool");
            (yyval.node).size = getSize("bool");
            strcpy((yyval.node).lexeme, "false");

            (yyval.node).TAC = nullCST();
            strcpy((yyval.node).res, (yyval.node).lexeme );
         }
#line 5181 "parser.tab.c"
    break;

  case 111: /* primaryExpr: NONE  */
#line 3397 "parser.y"
               { 
            debugging("primary expression, none", 1);
            (yyval.node).nodeNum = nodeInit("None");
            strcpy((yyval.node).type, "none");


            (yyval.node).size = 0;
            strcpy((yyval.node).type, "none");
            strcpy((yyval.node).lexeme, "none");

            (yyval.node).TAC = nullCST();
            strcpy((yyval.node).res, (yyval.node).lexeme );
        }
#line 5199 "parser.tab.c"
    break;

  case 112: /* primaryExpr: funccall  */
#line 3410 "parser.y"
                   { 
            debugging("function call", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            strcpy((yyval.node).type, (yyvsp[0].node).type);

            (yyval.node).TAC = (yyvsp[0].node).TAC;
            strcpy((yyval.node).res, (yyvsp[0].node).res );
        }
#line 5213 "parser.tab.c"
    break;

  case 113: /* primaryExpr: LPAREN expression RPAREN  */
#line 3419 "parser.y"
                                   { 
            (yyval.node).nodeNum = nodeInit("()");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-1].node).nodeNum);

            strcpy((yyval.node).type, (yyvsp[-1].node).type);

            string t = getTemp();
            string code = t + " = " + str((yyvsp[-1].node).res);
            (yyval.node).TAC = concat((yyvsp[-1].node).TAC, code);
            strcpy((yyval.node).res, t.c_str());

        }
#line 5230 "parser.tab.c"
    break;

  case 114: /* primaryExpr: LSQUARE listExpr RSQUARE  */
#line 3431 "parser.y"
                                   {
            (yyval.node).nodeNum = nodeInit("[]");
            ParentToChild((yyval.node).nodeNum, (yyvsp[-1].node).nodeNum);

            string temp((yyvsp[-1].node).type);
            string ltype = "list[" + temp + "]";
            strcpy((yyval.node).type, ltype.c_str()); 
            (yyval.node).list_size = (yyvsp[-1].node).list_size;

            //TODO

            string t = getTemp();
            string ret_temp = getTemp();
            string code = t + " = " + to_string((yyvsp[-1].node).list_size) + "*" + to_string(getSize((yyvsp[-1].node).type)) + "\npushparam " + t + "\ncall memalloc 1\npop_return " + ret_temp;

            code = code + "\n" + str((yyvsp[-1].node).res) + " = " + ret_temp;

            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            (yyval.node).TAC = concat((yyval.node).TAC, (yyvsp[-1].node).TAC);
            strcpy((yyval.node).res, (yyvsp[-1].node).res);

        }
#line 5258 "parser.tab.c"
    break;

  case 115: /* arguments: expression  */
#line 3461 "parser.y"
                   { 
            debugging("arguments", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            // string s = $1.type;
            // $$.par_arg_shape = s;
            strcpy((yyval.node).par_arg_shape, (yyvsp[0].node).type);
            (yyval.node).nelem = 1;

            string code = "pushparam " + str((yyvsp[0].node).res);
            (yyval.node).TAC = concat((yyvsp[0].node).TAC, code);
            strcpy((yyval.node).res, (yyvsp[0].node).res);

        }
#line 5277 "parser.tab.c"
    break;

  case 116: /* arguments: expression COMMA arguments  */
#line 3475 "parser.y"
                                     {
            debugging("arguments", 1);
            (yyval.node).nodeNum = nodeInit(",");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            (yyval.node).nelem = (yyvsp[0].node).nelem + 1;

            string s((yyvsp[-2].node).type);
            string curr((yyvsp[0].node).par_arg_shape);
            string comma = ",";
            curr = s+ comma + curr;
            strcpy((yyval.node).par_arg_shape, curr.c_str());

            string code = "pushparam " + str((yyvsp[-2].node).res);
            (yyval.node).TAC = concat((yyvsp[0].node).TAC, str((yyvsp[-2].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, code);

        }
#line 5301 "parser.tab.c"
    break;

  case 117: /* arguments: %empty  */
#line 3494 "parser.y"
             {
            (yyval.node).nodeNum = -1;
            (yyval.node).nelem = 0;
            string s = "";
            strcpy((yyval.node).par_arg_shape, s.c_str());

            (yyval.node).TAC = nullCST();
        }
#line 5314 "parser.tab.c"
    break;

  case 118: /* funccall: PRINT LPAREN arguments RPAREN  */
#line 3505 "parser.y"
                                        {
            debugging("funccall", 1);
            (yyval.node).nodeNum = nodeInit("funccall");
            string s = "print";
            ParentToChild((yyval.node).nodeNum, nodeInit(s));            
            int child = nodeInit("()");            
            ParentToChild((yyval.node).nodeNum, child);
            ParentToChild(child, (yyvsp[-1].node).nodeNum);

            if((yyvsp[-1].node).nelem != 1){
                yyerror("Predefined function call Error: Invalid print call. Make sure to pass a SINGLE primitve type expression");
            }
            
            if( strcmp((yyvsp[-1].node).par_arg_shape,"int")!=0 && strcmp((yyvsp[-1].node).par_arg_shape,"float")!=0 && strcmp((yyvsp[-1].node).par_arg_shape,"bool")!=0 && strcmp((yyvsp[-1].node).par_arg_shape,"str")!=0 ){
                yyerror("Predefined function call Error: Invalid print call. Make sure to pass a single PRIMITIVE(int,float,bool,str) type expression");
            }
            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-1].node).TAC));
            string code = "call PRINT 1";
            (yyval.node).TAC = concat((yyval.node).TAC, code);

            // strcpy($$.)

        }
#line 5343 "parser.tab.c"
    break;

  case 119: /* funccall: LEN LPAREN arguments RPAREN  */
#line 3529 "parser.y"
                                      {
            if((yyvsp[-1].node).nelem != 1){
                yyerror("Predefinged function call Error: Invalid len call. Make sure to pass a single expression of type <list>");
            }
            string shape = str((yyvsp[-1].node).par_arg_shape);
            if(shape.compare(0,4,"list")!=0){
                yyerror("Predefined function call Error: Invalid len call. Make sure to pass a list type expression");
            }

            yyerror("len operation is runtime result. not implemented yet. Do not call");
            

        }
#line 5361 "parser.tab.c"
    break;

  case 120: /* funccall: NAME LPAREN arguments RPAREN  */
#line 3543 "parser.y"
                                       {
            debugging("funccall", 1);
            (yyval.node).nodeNum = nodeInit("funccall");
            string s = (yyvsp[-3].text);
            ParentToChild((yyval.node).nodeNum, nodeInit(s));            
            int child = nodeInit("()");            
            ParentToChild((yyval.node).nodeNum, child);
            ParentToChild(child, (yyvsp[-1].node).nodeNum);

            //predefined functions 
            

            //check if declared
            SymbolEntry* funclookup = curr_table->lookup({(yyvsp[-3].text), (yyvsp[-1].node).par_arg_shape});
            
            // cout << "after lookup\n";
            if(funclookup){
                if(funclookup->token != "FUNC"){
                    //this ain't a function
                    cout << "function not defined" << endl;
                    yyerror("Function must be defined before use");
                }

                // if($3.nelem != funclookup->num_args){
                //     cout << "function " << $1 << "takes " << funclookup->num_args << " argument(s) but " << $3.nelem << " argument(s) were given"<< endl;
                //     yyerror("argument count mismatch") ;
                // }

                // //check funcs in current scope
                // string par_shape = curr_table->parShape($1);
                // //check funcs in global scope
                // if(par_shape == "$"){par_shape = (TablesList[0])->parShape($1);}
                // if(strcmp($3.par_arg_shape, par_shape.c_str())!=0){
                //     cout << "arguments type mismatch. required signature: " << par_shape << " but found "<< $3.par_arg_shape<<  endl;
                //     yyerror("Argument types mismatch");
                // }

                //ALLOK

                strcpy((yyval.node).type, funclookup->type.c_str());
                string code = "call " + found_table + "_" + str((yyvsp[-3].text)) + "_" + str((yyvsp[-1].node).par_arg_shape) + " " + to_string((yyvsp[-1].node).nelem);

                (yyval.node).TAC = nullCST();
                string pushra = "pushparam ra";
                (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-1].node).TAC));
                (yyval.node).TAC = concat((yyval.node).TAC, pushra);
                (yyval.node).TAC = concat((yyval.node).TAC, code);
                string t = getTemp();
                if(funclookup->type != "none"){
                    string code1 = "pop_return " + t;
                    (yyval.node).TAC = concat((yyval.node).TAC, code1);
                }
                strcpy((yyval.node).res, t.c_str());
                found_table = "";

            }
            else{
                cout << "function not defined OR given arguments do not match existing function signature, hence not resolved" << endl;
                yyerror("Function must be defined before use");
            }
        }
#line 5427 "parser.tab.c"
    break;

  case 121: /* funccall: NAME DOT methodcall  */
#line 3604 "parser.y"
                              { 
            (yyval.node).nodeNum = nodeInit("funccall");
            string s = (yyvsp[-2].text);
            int dot = nodeInit(".");
            ParentToChild((yyval.node).nodeNum, dot);
            ParentToChild(dot, nodeInit(s));
            ParentToChild(dot, (yyvsp[0].node).nodeNum);

            
            SymbolEntry* nEntry = curr_table->lookup({(yyvsp[-2].text),""});
            if(nEntry){
                //name exists: check if class object
                SymbolEntry* cEntry = curr_table->lookup({nEntry->type,""});
                if(!cEntry || cEntry->token != "CLASS"){
                    yyerror("Cannot invoke method");
                }
                //check if methodcall is method of that class or exists in parent
                SymbolTable* classTable = findTable(nEntry->type, "");
                if(!classTable){
                    yyerror("Invalid method invoked");
                }

                SymbolEntry* methodEntry = classTable->lookup({(yyvsp[0].node).lexeme, (yyvsp[0].node).par_arg_shape});
                if(!methodEntry){
                    cout << "method not defined OR given arguments do not match existing function signature hence not resolved" << endl;
                    yyerror("Function must be defined before use"); 
                }


                //ALLOK

                strcpy((yyval.node).type, (methodEntry->type).c_str());

                string code = "method_for " + str((yyvsp[-2].text)) + "\ncall " + found_table + "_" + str((yyvsp[0].node).lexeme) + "_" + str((yyvsp[0].node).par_arg_shape) + " " + to_string((yyvsp[0].node).nelem);
                (yyval.node).TAC = concat((yyvsp[0].node).TAC, code);
                string t = getTemp();
                string code1 = "pop_return " + t;
                (yyval.node).TAC = concat((yyval.node).TAC, code1);

                strcpy((yyval.node).res, t.c_str());

            }
            else{
                yyerror("Unknown Variable: Declare before use");

            }

        }
#line 5480 "parser.tab.c"
    break;

  case 122: /* methodcall: NAME LPAREN arguments RPAREN  */
#line 3655 "parser.y"
                                       {
            // cout << "inside method call" << endl;
            (yyval.node).nodeNum = nodeInit((yyvsp[-3].text));
            int parens = nodeInit("()");            
            ParentToChild((yyval.node).nodeNum, parens);
            ParentToChild(parens, (yyvsp[-1].node).nodeNum);

            strcpy((yyval.node).lexeme, (yyvsp[-3].text));
            (yyval.node).nelem = (yyvsp[-1].node).nelem;

            strcpy((yyval.node).par_arg_shape, (yyvsp[-1].node).par_arg_shape);

            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat((yyval.node).TAC, (yyvsp[-1].node).TAC);            
        }
#line 5500 "parser.tab.c"
    break;

  case 123: /* elif_action: %empty  */
#line 3672 "parser.y"
      {
        string succ_label = getLabel();
        successStk.push(succ_label);
        strcpy((yyval.node).success_, succ_label.c_str());
    }
#line 5510 "parser.tab.c"
    break;

  case 124: /* ifstatement: IF expression COLON Suite elif_action elifstmts elseblock  */
#line 3680 "parser.y"
                                                                  {
            debugging("if stmt", 1);
            (yyval.node).nodeNum = nodeInit("if");
            ParentToChild((yyval.node).nodeNum, (yyvsp[-5].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[-3].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[-1].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);


            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat((yyval.node).TAC, (yyvsp[-5].node).TAC);

            string code  = "ifz " + str((yyvsp[-5].node).res) + " goto " + str((yyvsp[-1].node).start_);
            (yyval.node).TAC = concat((yyval.node).TAC, code);

            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-3].node).TAC));  

            string suite_succ = "goto " + str((yyvsp[-2].node).success_); //universal success;
            (yyval.node).TAC = concat((yyval.node).TAC, suite_succ);

            string code1 = str((yyvsp[-1].node).start_) + " :" ;
            (yyval.node).TAC = concat((yyval.node).TAC, code1);
            //

            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-1].node).TAC));

            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-1].node).end_) + " :");

            (yyval.node).TAC = concat((yyval.node).TAC, (yyvsp[0].node).TAC);

            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-2].node).success_) + " :");

            successStk.pop();

        }
#line 5550 "parser.tab.c"
    break;

  case 125: /* ifstatement: IF expression COLON Suite elif_action elifstmts  */
#line 3715 "parser.y"
                                                          { 
            debugging("if stmt", 1);
            (yyval.node).nodeNum = nodeInit("if");
            ParentToChild((yyval.node).nodeNum, (yyvsp[-4].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);


            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat((yyval.node).TAC, (yyvsp[-4].node).TAC);

            string code  = "ifz " + str((yyvsp[-4].node).res) + " goto " + str((yyvsp[0].node).start_);
            (yyval.node).TAC = concat((yyval.node).TAC, code);

            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-2].node).TAC));

            string code1 = "goto " + str((yyvsp[-1].node).success_);
            (yyval.node).TAC = concat((yyval.node).TAC, code1);

            string code2 = str((yyvsp[0].node).start_) + ":";
            (yyval.node).TAC = concat((yyval.node).TAC, code2);
            
            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[0].node).TAC));

            string code4 = str((yyvsp[0].node).end_) + " :";
            (yyval.node).TAC = concat((yyval.node).TAC, code4);

            string code3 = str((yyvsp[-1].node).success_) + ":\n";
            (yyval.node).TAC = concat((yyval.node).TAC, code3);

        }
#line 5586 "parser.tab.c"
    break;

  case 126: /* ifstatement: IF expression COLON Suite elseblock  */
#line 3746 "parser.y"
                                              { 
            debugging("if stmt", 1);
            (yyval.node).nodeNum = nodeInit("if");
            ParentToChild((yyval.node).nodeNum, (yyvsp[-3].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[-1].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat((yyval.node).TAC, (yyvsp[-3].node).TAC);

            string code  = "ifz " + str((yyvsp[-3].node).res) + " goto " + str((yyvsp[0].node).start_);
            (yyval.node).TAC = concat((yyval.node).TAC, code);

            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-1].node).TAC));

            string code1 = "goto " + str((yyvsp[0].node).end_);
            (yyval.node).TAC = concat((yyval.node).TAC, code1);

            string code2 = str((yyvsp[0].node).start_) + ":";
            (yyval.node).TAC = concat((yyval.node).TAC, code2);

            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[0].node).TAC));

            string code3 = str((yyvsp[0].node).end_) + ":";
            (yyval.node).TAC = concat((yyval.node).TAC, code3);
            
        }
#line 5618 "parser.tab.c"
    break;

  case 127: /* ifstatement: IF expression COLON Suite  */
#line 3773 "parser.y"
                                    { 
            debugging("if stmt", 1);
            (yyval.node).nodeNum = nodeInit("if");
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-2].node).TAC));

            string code  = "ifz " + str((yyvsp[-2].node).res) + " goto " + str((yyvsp[0].node).end_label);
            (yyval.node).TAC = concat((yyval.node).TAC, code);

            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[0].node).TAC));

            string code1 = str((yyvsp[0].node).end_label) + ":";
            (yyval.node).TAC = concat((yyval.node).TAC, code1);

        }
#line 5641 "parser.tab.c"
    break;

  case 128: /* elifstmt: ELIF expression COLON Suite  */
#line 3793 "parser.y"
                                     {
            debugging("elifstmt", 1);
            (yyval.node).nodeNum = nodeInit("elif");
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            string sl = getLabel();
            string el = getLabel();

            (yyval.node).TAC = nullCST();

            (yyval.node).TAC = concat((yyval.node).TAC, (yyvsp[-2].node).TAC);
            
            string code = "ifz " + str((yyvsp[-2].node).res) + " goto " + el;
            (yyval.node).TAC = concat((yyval.node).TAC, code);

            (yyval.node).TAC = concat((yyval.node).TAC, (yyvsp[0].node).TAC);

            string succ = successStk.top();
            (yyval.node).TAC = concat((yyval.node).TAC, "goto " + succ);

            strcpy((yyval.node).end_label, (yyvsp[0].node).end_label);
            strcpy((yyval.node).start_, sl.c_str());
            strcpy((yyval.node).end_, el.c_str());

         }
#line 5672 "parser.tab.c"
    break;

  case 129: /* elifstmts: elifstmt  */
#line 3822 "parser.y"
                            { 
            debugging("elifstmts", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            (yyval.node).TAC = (yyvsp[0].node).TAC;
            strcpy((yyval.node).end_label, (yyvsp[0].node).end_label);       //added in ifstmt or as elifstmsts

            strcpy((yyval.node).start_, (yyvsp[0].node).start_);
            strcpy((yyval.node).end_, (yyvsp[0].node).end_);
        }
#line 5687 "parser.tab.c"
    break;

  case 130: /* elifstmts: elifstmts elifstmt  */
#line 3832 "parser.y"
                               {
            debugging("elifstmts", 1);
            (yyval.node).nodeNum = nodeInit("elif");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-1].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            // $$.TAC = concat($1.TAC, str($2.TAC));
            // strcpy($$.end_label, $2.end_label);

            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat((yyval.node).TAC, (yyvsp[-1].node).TAC);

            string code = str((yyvsp[-1].node).end_) + ":";
            (yyval.node).TAC = concat((yyval.node).TAC, code);

            (yyval.node).TAC = concat((yyval.node).TAC, (yyvsp[0].node).TAC);

            strcpy((yyval.node).end_label, (yyvsp[0].node).end_label); //added in ifstmt
            strcpy((yyval.node).start_, (yyvsp[-1].node).start_);
            strcpy((yyval.node).end_, (yyvsp[0].node).end_);
        }
#line 5713 "parser.tab.c"
    break;

  case 131: /* elseblock: ELSE COLON Suite  */
#line 3859 "parser.y"
                          { 
            debugging("elseblock", 1);
            (yyval.node).nodeNum = nodeInit("else");
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat((yyval.node).TAC, (yyvsp[0].node).TAC);

            string sl = getLabel();
            string el = getLabel();
            strcpy((yyval.node).start_, sl.c_str());            
            strcpy((yyval.node).end_, el.c_str());
        }
#line 5731 "parser.tab.c"
    break;

  case 132: /* forstmt: FOR forexpr COLON loop_action Suite elseblock  */
#line 3875 "parser.y"
                                                       {
            debugging("for stmt", 1);
            (yyval.node).nodeNum = nodeInit("for");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-4].node).nodeNum);            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[-1].node).nodeNum);

            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-4].node).res)+" = "+str((yyvsp[-4].node).range_start)+" - "+str((yyvsp[-4].node).range_step));
            
            string loop_start = str((yyvsp[-2].node).cont_);
            (yyval.node).TAC = concat((yyval.node).TAC, loop_start + " :");
            
            string code = str((yyvsp[-4].node).res)+" = "+str((yyvsp[-4].node).res)+" + "+str((yyvsp[-4].node).range_step);
            (yyval.node).TAC = concat((yyval.node).TAC, code);

            string cond = getTemp();
            code = cond+" = "+str((yyvsp[-4].node).res)+" < "+str((yyvsp[-4].node).range_end);
            (yyval.node).TAC = concat((yyval.node).TAC, code);

            code = "ifz "+cond+" goto "+str((yyvsp[-1].node).end_label);
            (yyval.node).TAC = concat((yyval.node).TAC, code);

            (yyval.node).TAC = concat((yyval.node).TAC, (yyvsp[-1].node).TAC);

            code = "goto "+loop_start;
            (yyval.node).TAC = concat((yyval.node).TAC, code);

            code = str((yyvsp[-1].node).end_label)+" :";
            (yyval.node).TAC = concat((yyval.node).TAC,code);

            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[0].node).TAC));

            code = str((yyvsp[-2].node).break_)+" :";
            (yyval.node).TAC = concat((yyval.node).TAC, code);

            // cout << "done for stmt\n";

            breakStk.pop();
            contStk.pop();

         }
#line 5778 "parser.tab.c"
    break;

  case 133: /* forstmt: FOR forexpr COLON loop_action Suite  */
#line 3917 "parser.y"
                                               {
            debugging("for stmt", 1);
            (yyval.node).nodeNum = nodeInit("for");
            ParentToChild((yyval.node).nodeNum, (yyvsp[-3].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[-1].node).nodeNum);

            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-3].node).res)+" = "+str((yyvsp[-3].node).range_start)+" - "+str((yyvsp[-3].node).range_step));

            string loop_start = str((yyvsp[-1].node).cont_);
            (yyval.node).TAC = concat((yyval.node).TAC, loop_start + " :");
            
            string code = str((yyvsp[-3].node).res)+" = "+str((yyvsp[-3].node).res)+" + "+str((yyvsp[-3].node).range_step);
            (yyval.node).TAC = concat((yyval.node).TAC, code);

            string cond = getTemp();
            code = cond+" = "+str((yyvsp[-3].node).res)+" < "+str((yyvsp[-3].node).range_end);
            (yyval.node).TAC = concat((yyval.node).TAC, code);

            code = "ifz "+cond+" goto "+str((yyvsp[-1].node).break_);
            (yyval.node).TAC = concat((yyval.node).TAC, code);

            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[0].node).TAC));


            code = "goto "+loop_start;
            (yyval.node).TAC = concat((yyval.node).TAC, code);

            code = str((yyvsp[-1].node).break_)+ " :";
            (yyval.node).TAC = concat((yyval.node).TAC, code);


            breakStk.pop();
            contStk.pop();
            // cout << "done for stmt1\n";

         }
#line 5820 "parser.tab.c"
    break;

  case 134: /* ForList: RANGE LPAREN expression COMMA expression COMMA expression RPAREN  */
#line 3957 "parser.y"
                                                                          {

            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat((yyval.node).TAC, (yyvsp[-5].node).TAC);
            strcpy((yyval.node).range_start, (yyvsp[-5].node).res);
            strcpy((yyval.node).range_end, (yyvsp[-3].node).res);
            strcpy((yyval.node).range_step, (yyvsp[-1].node).res);

            //cant check start < end condition
            //runtime variable right??

        }
#line 5837 "parser.tab.c"
    break;

  case 135: /* ForList: funccall  */
#line 3969 "parser.y"
                     {
            debugging("for list", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;
            (yyval.node) = (yyvsp[0].node);

            yyerror("for loop only to be run using range function");

            //check if funccall type is list
            string ftype((yyvsp[0].node).type);
            if( ftype.compare(0,4,"list")!=0){
                cout << "TypeError: "<< "Function return type is <"<< ftype<< "> , but expected is a <list>" << endl;
                yyerror("Functtion return type is not a list");

                (yyval.node).TAC = (yyvsp[0].node).TAC;
                strcpy((yyval.node).res, (yyvsp[0].node).res);
            }
         }
#line 5859 "parser.tab.c"
    break;

  case 136: /* ForList: ids  */
#line 3986 "parser.y"
               {
            debugging("for list", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;

            yyerror("for loop only to be run using range function");

            //check if declared
            SymbolEntry* idslookup = curr_table->lookup({(yyvsp[0].node).lexeme,""});
            if(idslookup){
                //exists: OK
                //check if list
                if(idslookup->type.compare(0,4,"list")!=0){
                    //not a list
                    cout << "TypeError" << endl;
                    yyerror("Expected type list");
                }

                strcpy((yyval.node).type,(idslookup->type).c_str());

                (yyval.node).TAC = (yyvsp[0].node).TAC;
                strcpy((yyval.node).res, (yyvsp[0].node).res);
            }
            else{
                //does not exits
                yyerror("Variable not declared");
            }

        }
#line 5892 "parser.tab.c"
    break;

  case 137: /* ForList: LSQUARE listExpr RSQUARE  */
#line 4014 "parser.y"
                                   {
            debugging("for list", 1);
            (yyval.node).nodeNum = nodeInit("[]");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-1].node).nodeNum);

            yyerror("for loop only to be run using range function");

            string temp((yyvsp[-1].node).type);
            temp = "list[" + temp + "]";
            strcpy((yyval.node).type, temp.c_str());

            //TODO
            //but list iteration can be ommitted

            (yyval.node).TAC = nullCST();
            strcpy((yyval.node).res, (yyvsp[-1].node).res);

            
            
        }
#line 5917 "parser.tab.c"
    break;

  case 138: /* loop_action: %empty  */
#line 4036 "parser.y"
      {
        string break_label = getLabel();
        breakStk.push(break_label);
        strcpy((yyval.node).break_, break_label.c_str());

        string cont_label = getLabel();
        contStk.push(cont_label);
        strcpy((yyval.node).cont_, cont_label.c_str());
    }
#line 5931 "parser.tab.c"
    break;

  case 139: /* whilestatement: WHILE expression COLON loop_action Suite elseblock  */
#line 4047 "parser.y"
                                                            {
            debugging("while stmt", 1);
            (yyval.node).nodeNum = nodeInit("while");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-4].node).nodeNum);            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[-1].node).nodeNum);

            (yyval.node).TAC = nullCST();
            
            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-2].node).cont_) + ":" );

            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-4].node).TAC));

            string code = "ifz " + str((yyvsp[-4].node).res) + " goto " + str((yyvsp[-1].node).end_label);
            (yyval.node).TAC = concat((yyval.node).TAC, code);

            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-1].node).TAC));

            (yyval.node).TAC = concat((yyval.node).TAC, "goto " + str((yyvsp[-2].node).cont_));

            string code2 = str((yyvsp[-1].node).end_label) + " :";
            (yyval.node).TAC = concat((yyval.node).TAC, code2);

            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[0].node).TAC));

            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-2].node).cont_) + " :");

            breakStk.pop();
            contStk.pop();

         }
#line 5967 "parser.tab.c"
    break;

  case 140: /* whilestatement: WHILE expression COLON loop_action Suite  */
#line 4078 "parser.y"
                                                    { 
            debugging("while stmt", 1);
            (yyval.node).nodeNum = nodeInit("while");            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-3].node).nodeNum);            
            ParentToChild((yyval.node).nodeNum, (yyvsp[-1].node).nodeNum);

            (yyval.node).TAC = nullCST();

            string loopstart = getLabel();
            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-1].node).cont_) + ":" );

            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-3].node).TAC));

            string code = "ifz " + str((yyvsp[-3].node).res) + " goto " + str((yyvsp[-1].node).break_);
            (yyval.node).TAC = concat((yyval.node).TAC, code);

            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[0].node).TAC));

            (yyval.node).TAC = concat((yyval.node).TAC, "goto " + str((yyvsp[-1].node).cont_));

            string code1 = str((yyvsp[-1].node).break_) + " :";
            (yyval.node).TAC = concat((yyval.node).TAC, code1);

            breakStk.pop();
            contStk.pop();

        }
#line 5999 "parser.tab.c"
    break;

  case 141: /* parameters: vardeclaration  */
#line 4109 "parser.y"
                        {
            debugging("parameters", 1);
            (yyval.node) = (yyvsp[0].node);

            (yyval.node).nelem = 1;
            if(param_num==-1){param_num = 1;}
            else {param_num ++;}

            fparams.push_back({{(yyvsp[0].node).lexeme,yylineno},{(yyvsp[0].node).type, param_num}});
            strcpy((yyval.node).par_arg_shape, (yyvsp[0].node).type);

            (yyval.node).TAC = nullCST();
            string code = str((yyvsp[0].node).res) + " popparam ";
            (yyval.node).TAC = concat((yyval.node).TAC, code);

        }
#line 6020 "parser.tab.c"
    break;

  case 142: /* parameters: parameters COMMA vardeclaration  */
#line 4125 "parser.y"
                                          {
            debugging("parameters", 1);
            (yyval.node).nodeNum = nodeInit(",");
            ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            (yyval.node).nelem = (yyvsp[-2].node).nelem + 1;
            if(param_num==-1){param_num = 1;}
            else {param_num ++;}

            fparams.push_back({{(yyvsp[0].node).lexeme,yylineno},{(yyvsp[0].node).type, param_num}});

            string curr((yyvsp[-2].node).par_arg_shape);
            string comma(",");
            string s((yyvsp[0].node).type);
            curr = curr + comma + s;
            strcpy((yyval.node).par_arg_shape, curr.c_str());

            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-2].node).TAC));

            string code = str((yyvsp[0].node).res) + " popparam ";
            (yyval.node).TAC = concat((yyval.node).TAC, code);

        }
#line 6050 "parser.tab.c"
    break;

  case 143: /* parameters: NAME  */
#line 4150 "parser.y"
               {
            debugging("parameters", 1);
            string t= (yyvsp[0].text);
            string s = "ID(" +t + ")";
            (yyval.node).nodeNum = nodeInit(s);

            //name must be self
            if(strcmp((yyvsp[0].text), "self")!=0){
                //not self
                yyerror("Type hint must be provided for function definition");
            }
            
            //self is of type, classname which is the curr_table
            strcpy((yyval.node).par_arg_shape, curr_table->TableName.c_str());

            //TODO

            (yyval.node).TAC = nullCST();

            string code = str((yyvsp[0].text)) + " popparam ";
            (yyval.node).TAC = concat((yyval.node).TAC, code);
            
        }
#line 6078 "parser.tab.c"
    break;

  case 144: /* parameters: %empty  */
#line 4173 "parser.y"
            {
            debugging("parameters", 1);
            (yyval.node).nodeNum = -1;
            (yyval.node).nelem = 0;
            strcpy((yyval.node).type, "none");

            strcpy((yyval.node).par_arg_shape, "");

            (yyval.node).TAC = nullCST();


        }
#line 6095 "parser.tab.c"
    break;

  case 145: /* returnType: primitiveType  */
#line 4188 "parser.y"
                      { 
            debugging("return type", 1);
            (yyval.node).nodeNum = (yyvsp[0].node).nodeNum;
            strcpy((yyval.node).type, (yyvsp[0].node).type);
            (yyval.node) = (yyvsp[0].node);

            (yyval.node).TAC = (yyvsp[0].node).TAC;
        }
#line 6108 "parser.tab.c"
    break;

  case 146: /* returnType: NONE  */
#line 4197 "parser.y"
               { 
            debugging("return type", 1);
            (yyval.node).nodeNum = nodeInit("None");
            strcpy((yyval.node).type, "none");            

            (yyval.node).TAC = nullCST();
        }
#line 6120 "parser.tab.c"
    break;

  case 147: /* forexpr: NAME IN ForList  */
#line 4209 "parser.y"
                           { 
            debugging("for expression", 1);
            (yyval.node).nodeNum = nodeInit("in");
            string t= (yyvsp[-2].text);
            string s = "ID(" +t + ")";
            ParentToChild((yyval.node).nodeNum, nodeInit(s));
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            //if new name then create new entry 
            // char ntype[100];
            // int y = 0;
            // for(int i=5; i< strlen($3.type)-1 ; i++){
            //     ntype[y] = ($3.type)[i];
            //     y++;
            // }
            // ntype[y] = '\0';
            // string sntype(ntype);

            SymbolEntry* namelookup = curr_table->lookup({(yyvsp[-2].text),""});
            if(!namelookup){
                curr_table->entry((yyvsp[-2].text), "", "NAME", "int", getSize("int") , offset,curr_scope_name, yylineno, 0, 0);
                offset = offset + getSize(((yyvsp[0].node)).type);

                (yyval.node).TAC = nullCST();
                strcpy((yyval.node).res, (yyvsp[-2].text));
                strcpy((yyval.node).range_start, (yyvsp[0].node).range_start);
                strcpy((yyval.node).range_end, (yyvsp[0].node).range_end);
                strcpy((yyval.node).range_step, (yyvsp[0].node).range_step);

            }
            else{
                //exists, so need to check if type matches
                if(namelookup->type != "int"){
                    cout<< "TypeError: " << "expected type <"<< "int" << ">, and found <"<< namelookup->type << "> "<< endl;;
                    yyerror("loop variable type mismatch");
                }

                (yyval.node).TAC = nullCST();
                strcpy((yyval.node).res, (yyvsp[-2].text));
                strcpy((yyval.node).range_start, (yyvsp[0].node).range_start);
                strcpy((yyval.node).range_end, (yyvsp[0].node).range_end);
                strcpy((yyval.node).range_step, (yyvsp[0].node).range_step);

            }

        }
#line 6171 "parser.tab.c"
    break;

  case 148: /* funcdef: funcheader Suite  */
#line 4259 "parser.y"
                          { 
            (yyval.node) = (yyvsp[-1].node);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            //after func def
            curr_table = tableStk.top();
            tableStk.pop();

            curr_scope_name = scopeStk.top();
            scopeStk.pop();

            offset = offsetStk.top();
            offsetStk.pop();

            (yyval.node).TAC = nullCST();
            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-1].node).TAC));
            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[0].node).TAC));

            string endfunc = "goto ra\nendfunc";
            (yyval.node).TAC = concat((yyval.node).TAC,endfunc);
        }
#line 6197 "parser.tab.c"
    break;

  case 149: /* funcheader: DEF NAME LPAREN parameters RPAREN RARR returnType COLON  */
#line 4283 "parser.y"
                                                                  {
            (yyval.node).nodeNum = nodeInit("def");
            string t= (yyvsp[-6].text);
            string s = "ID(" +t + ")";
            ParentToChild((yyval.node).nodeNum, nodeInit(s));            
            int parens=nodeInit("()");            
            ParentToChild(parens, (yyvsp[-4].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, parens);
            ParentToChild((yyval.node).nodeNum, (yyvsp[-1].node).nodeNum); 

            //check if func name already exists
            string scope_of_func = curr_table->TableName;
            SymbolEntry* funcEntry = curr_table->lookup({(yyvsp[-6].text),(yyvsp[-4].node).par_arg_shape});
            if(funcEntry){
                cout << "Function definition with same signature already exists" << endl;
                yyerror("Function/Method redeclaration");
            }

            // cout << "par arg shape: " << $4.par_arg_shape << endl;
            curr_table->entry((yyvsp[-6].text), (yyvsp[-4].node).par_arg_shape, "FUNC", (yyvsp[-1].node).type, getSize((yyvsp[-1].node).type), offset, curr_scope_name, yylineno, (yyvsp[-4].node).nelem, 0);
            offset += getSize((yyvsp[-1].node).type);

            tableStk.push(curr_table);
            curr_table = new SymbolTable(curr_table, (yyvsp[-6].text), (yyvsp[-4].node).par_arg_shape);
            TablesList.push_back(curr_table);

            scopeStk.push(curr_scope_name);
            curr_scope_name = "func";

            offsetStk.push(offset);
            offset = 0;

            strcpy(curr_return_type, (yyvsp[-1].node).type);

            for( int i=0; i<fparams.size(); i++){
                curr_table->entry(fparams[i].first.first, "", "PARAM", fparams[i].second.first, getSize(fparams[i].second.first), offset, curr_scope_name, fparams[i].first.second, 0, fparams[i].second.second);

                offset += getSize(fparams[i].second.first);
            }

            fparams.clear();
            param_num = -1;

            (yyval.node).TAC = nullCST();
        
            string code = "begin func " + scope_of_func + "_" + str((yyvsp[-6].text)) + "_" + str((yyvsp[-4].node).par_arg_shape) + " :\nra popparam";

            
            (yyval.node).TAC = concat((yyval.node).TAC, code);

            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-4].node).TAC));

            found_table = "";


        }
#line 6258 "parser.tab.c"
    break;

  case 150: /* funcheader: DEF NAME LPAREN parameters RPAREN COLON  */
#line 4339 "parser.y"
                                                  {
            (yyval.node).nodeNum = nodeInit("def");
            string t= (yyvsp[-4].text);
            string s = "ID(" +t + ")";
            ParentToChild((yyval.node).nodeNum, nodeInit(s));            
            int parens=nodeInit("()");            
            ParentToChild(parens, (yyvsp[-2].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, parens);

            //do sig checks and then push
            string scope_of_func = curr_table->TableName;
            SymbolEntry* funcEntry = curr_table->lookup({(yyvsp[-4].text),(yyvsp[-2].node).par_arg_shape});
            if(funcEntry){
                cout << "Function definition with same signature already exists" << endl;
                yyerror("Function/Method redeclaration");
            }

            // cout << "par arg shape: " << $4.par_arg_shape << endl;
            curr_table->entry((yyvsp[-4].text), (yyvsp[-2].node).par_arg_shape , "FUNC", "none", getSize("none"), offset, curr_scope_name, yylineno, (yyvsp[-2].node).nelem, 0 );
            offset += getSize("none");

            tableStk.push(curr_table);
            curr_table = new SymbolTable(curr_table, (yyvsp[-4].text), (yyvsp[-2].node).par_arg_shape);
            TablesList.push_back(curr_table);

            scopeStk.push(curr_scope_name);
            curr_scope_name = "func";

            offsetStk.push(offset);
            offset = 0;

            strcpy(curr_return_type, "none");

            for( int i=0; i<fparams.size(); i++){
                curr_table->entry(fparams[i].first.first, "", "PARAM", fparams[i].second.first, getSize(fparams[i].second.first), offset, curr_scope_name, fparams[i].first.second, 0, fparams[i].second.second);

                offset += getSize(fparams[i].second.first);
            }

            fparams.clear();
            param_num = -1;

            (yyval.node).TAC = nullCST();
            
            string code = "beginfunc "+scope_of_func + "_" + str((yyvsp[-4].text)) + "_" + str((yyvsp[-2].node).par_arg_shape) + " :\nra popparam";

            (yyval.node).TAC = concat((yyval.node).TAC, code);

            (yyval.node).TAC = concat((yyval.node).TAC, str((yyvsp[-2].node).TAC));

            found_table = "";
        }
#line 6315 "parser.tab.c"
    break;

  case 151: /* classdef: classheader COLON Suite  */
#line 4394 "parser.y"
                                   { 
            debugging("class definition", 1);
            (yyval.node).nodeNum = (yyvsp[-2].node).nodeNum;
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);

            curr_table = tableStk.top();
            tableStk.pop();

            curr_scope_name = scopeStk.top();
            scopeStk.pop();

            offset = offsetStk.top();
            offsetStk.pop();

            (yyval.node).TAC = (yyvsp[0].node).TAC;


        }
#line 6338 "parser.tab.c"
    break;

  case 152: /* classdef: classheader LPAREN classarguments RPAREN COLON Suite  */
#line 4412 "parser.y"
                                                                { 
            debugging("class definition", 1);
            (yyval.node).nodeNum = (yyvsp[-5].node).nodeNum;
            int PARs = nodeInit("()");
            ParentToChild(PARs, (yyvsp[-3].node).nodeNum);
            ParentToChild((yyval.node).nodeNum, PARs);
            ParentToChild((yyval.node).nodeNum, (yyvsp[0].node).nodeNum);
            
            //curr_table is abhi ke class ka table
            //find the parent classes and put this as child
            SymbolTable* parent_table = findTable((yyvsp[-3].node).lexeme,"");
            curr_table->Parent = parent_table;
            parent_table->childTables.push_back(curr_table);

            curr_table = tableStk.top();
            tableStk.pop();

            curr_scope_name = scopeStk.top();
            scopeStk.pop();

            offset = offsetStk.top();
            offsetStk.pop();

            (yyval.node).TAC = (yyvsp[0].node).TAC;
        }
#line 6368 "parser.tab.c"
    break;

  case 153: /* classheader: CLASS NAME  */
#line 4440 "parser.y"
                 {
        (yyval.node).nodeNum = nodeInit("classdef");
        ParentToChild((yyval.node).nodeNum, nodeInit((yyvsp[0].text)));

        class_list.push_back({(yyvsp[0].text),curr_scope_name});

        curr_table->entry((yyvsp[0].text),"", "CLASS", "class", getSize("class"), offset, curr_scope_name, yylineno, 0, 0); //num-args argnum

        offset += getSize("class");

        tableStk.push(curr_table);
        curr_table = new SymbolTable(curr_table, (yyvsp[0].text), "");
        curr_table->entry("self", "", "PARAM", (yyvsp[0].text), getSize("class"), offset, "class", yylineno, 0, 0);
        offset += getSize("class");
        TablesList.push_back(curr_table);

        scopeStk.push(curr_scope_name);
        curr_scope_name = "class";

        offsetStk.push(offset);
        offset = 0;

        (yyval.node).TAC = nullCST();
        strcpy((yyval.node).res, (yyvsp[0].text));

    }
#line 6399 "parser.tab.c"
    break;

  case 154: /* classarguments: NAME  */
#line 4468 "parser.y"
           {
        debugging("classarguments",1);
        (yyval.node).nodeNum = nodeInit((yyvsp[0].text));

        //curr scope is that of this new class
        (yyval.node).nelem = 1;
        //check if argument exists as class
        SymbolEntry* classEntry = curr_table->lookup({(yyvsp[0].text),""});
        if(classEntry){
            if(classEntry->token != "CLASS"){
                cout << "TypeError: expected type <class> but found " << classEntry->token << endl;
                yyerror("Arguments to class definition must be defined class");
            }

            //OK
            //take variables of this class and add them in this table
            SymbolTable* parentClass = findTable((yyvsp[0].text), "");
            for(auto it: parentClass->Table){
                if(it.second.type != "PARAM" || it.second.token!="FUNC"){
                    curr_table->entry(it.first.first,"", it.second.token, it.second.type, it.second.size, it.second.offset, curr_scope_name, yylineno, it.second.num_args, it.second.arg_num );
                }
                offset = offset + it.second.size;
            }
            strcpy((yyval.node).lexeme, (yyvsp[0].text));
        }
        else{
            yyerror("Argument not valid class");
        }
        
        
    }
#line 6435 "parser.tab.c"
    break;

  case 155: /* classarguments: classarguments COMMA NAME  */
#line 4499 "parser.y"
                                { //multiple inheritance anyways not allowed
        (yyval.node).nodeNum = nodeInit(",");
        ParentToChild((yyval.node).nodeNum, (yyvsp[-2].node).nodeNum);
        ParentToChild((yyval.node).nodeNum, nodeInit((yyvsp[0].text)));

        (yyval.node).nelem = (yyvsp[-2].node).nelem + 1;
        //check if argument exists as class
        SymbolEntry* classEntry = curr_table->lookup({(yyvsp[0].text),""});
        if(classEntry){
            if(classEntry->token != "CLASS"){
                cout << "TypeError: expected type <class> but found " << classEntry->token << endl;
                yyerror("Arguments to class definition must be defined class");
            }
        }
        else{
            yyerror("Argument not valid class");
        }

    }
#line 6459 "parser.tab.c"
    break;

  case 156: /* classarguments: %empty  */
#line 4519 "parser.y"
      {
        (yyval.node).nodeNum = -1;
        (yyval.node).nelem = 0;
    }
#line 6468 "parser.tab.c"
    break;

  case 157: /* Suite: normalstmt NEWLINE  */
#line 4526 "parser.y"
                           { 
            debugging("suite", 1);
            (yyval.node).nodeNum = (yyvsp[-1].node).nodeNum;
            (yyval.node) = (yyvsp[-1].node);

            string s_end = getLabel();
            strcpy((yyval.node).end_label, s_end.c_str());

            (yyval.node).TAC = (yyvsp[-1].node).TAC;

        }
#line 6484 "parser.tab.c"
    break;

  case 158: /* Suite: NEWLINE INDENT stmts DEDENT  */
#line 4537 "parser.y"
                                      { 
            // cout << "-----------------" << endl;
            (yyval.node).nodeNum = (yyvsp[-1].node).nodeNum;
            (yyval.node) = (yyvsp[-1].node);

            strcpy((yyval.node).end_label, (yyvsp[-1].node).end_label);
            (yyval.node).TAC = (yyvsp[-1].node).TAC;
        }
#line 6497 "parser.tab.c"
    break;

  case 159: /* ending: NEWLINE ending  */
#line 4548 "parser.y"
                          {
            debugging("ending", 1);
            (yyval.node).nodeNum=nodeInit("newline"); 

            (yyval.node).TAC = nullCST();
            
            }
#line 6509 "parser.tab.c"
    break;

  case 160: /* ending: ENDMARKER  */
#line 4555 "parser.y"
                    { 
            debugging("ending", 1);
            (yyval.node).nodeNum=nodeInit("EOF"); 

            (yyval.node).TAC = nullCST();            
        }
#line 6520 "parser.tab.c"
    break;


#line 6524 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 4563 "parser.y"


int main(int argc, char **argv){

    //find if --debug flag is present in the command the arguments
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "--debug") == 0){
            debug = 1;
            break;
        }
    }

    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "--st") == 0){
            for(auto it: TablesList){
                it->print_table();
                cout << "---------------------\n------------------" << endl;
            }
            break;
        }
    }

    int parsed  = 0;

    //search if -f (file input) is present in the command line arguments
    for(int i = 0; i<argc; i++){
        if(strcmp(argv[i], "-input") == 0){
            if(i+1 < argc){
                FILE *fp = fopen(argv[i+1], "r");
                if(fp){

                    yyin = fp;
                    yyparse();
                    parsed = 1;
                    fclose(fp);
                }
                else{
                    printf("Error: File not found\n");
                    return 1;
                }
            }
            else{
                printf("Error: File not found\n");
                return 1;
            }
        }
    }

    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "-3ac") == 0){
            ofstream tac_file("_3AC.txt");

            if(!tac_file){
                cerr << "Error in creating _3AC.txt";
                return 1;
            }
            string final_3AC = "";
            istringstream iss(TAC_output);
            string line;

            // Iterate through each line of the string
            while (getline(iss, line)) {
                // Print each line
                if(line.length()==0){
                    continue;
                }
                if(line.back() != ':'){
                    final_3AC = final_3AC + "\t" + line + "\n";
                }else{
                    final_3AC = final_3AC + line + "\n";
                }
            }
            
            tac_file << final_3AC;
            tac_file.close();
        }
    }

    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "-sym") == 0){
            ofstream out("symbol_tables.csv");

            if(!out.is_open()){
                cerr << "Failed to open symbol_tables.csv";
                return 1;
            }
            for(auto it: TablesList){
                string c = "";
                for(auto jt: it->childTables){
                    c = c + "," + jt->TableName;
                }

                out << ",,,,,,,," << endl;
                if(it->Parent){
                    out << "TableName:,"<< it->TableName << ",Parent: " << it->Parent->TableName << ",Child(s): " << c << endl;

                }else{
                    out << "TableName:,"<< it->TableName << ",Parent: " << "NULL" <<  ",Child(s): " << c << endl;
                }

                out << "Name,Signature,Token,Type,Size,Offset,LineNo,NumArgs,ArgNum" << std::endl;

                for(auto kt: it->Table) {
                    out << kt.first.first << ","<< kt.first.second << ","<<kt.second.token << "," << kt.second.type << ","<< kt.second.size << ","<< kt.second.offset << ","<< kt.second.lineno << ","<< kt.second.num_args << ","<< kt.second.arg_num << endl;
                }
                out << "\n\n";
            }

            out.close();
        }
    }

    if(parsed == 0){
        yyin = stdin;
        yyparse();
    }

    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "-ast") == 0){
            string filename = "AST.dot";
            write_gv(filename);
        }
    }


    
    gen_global();
    gen_text();

    print_code(asm_file);

    


    return 0;
}

void yyerror(const char *message)
{
    //error with line no and message with yytext
    fprintf(stderr, "Error at line %d: %s\n", yylineno, message);
    fprintf(stderr, "%s\n",yytext);
    fprintf(stderr, "^\n");
    exit(EXIT_FAILURE); 
} 

/*
errors in asm file:
space before labels and main
commas when 2 registers are being used
*/
