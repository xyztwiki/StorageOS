#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MEMORY_SIZE 256
#define NUM_REGISTERS 16
#define uint2_t 
#define uint4_t
#define uint6_t
#define uint8_t
// Instruction format
typedef struct {
    uint2_t opcode : 2;
    uint4_t rd : 4;
    uint6_t rs1 : 6;
    uint8_t rs2 : 8;
} Instruction;

// CPU structure
typedef struct {
    uint32_t registers[NUM_REGISTERS];
    uint32_t pc;  // Program Counter
    uint8_t memory[MEMORY_SIZE];
} CPU;

// Opcodes
enum {
    ADD = 0,
    SUB,
    AND,
    OR,
    XOR,
    SLL,
    SRL,
    LDR,
    STR,
    BEQ,
    HALT
};

// Initialize CPU
void init_cpu(CPU *cpu) {
    for (int i = 0; i < NUM_REGISTERS; i++) {
        cpu->registers[i] = 0;
    }
    cpu->pc = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        cpu->memory[i] = 0;
    }
}

// Fetch instruction from memory
Instruction fetch(CPU *cpu) {
    Instruction instr;
    uint16_t raw_instr = (cpu->memory[cpu->pc] << 8) | cpu->memory[cpu->pc + 1];
    instr.opcode = (raw_instr >> 12) & 0xF;
    instr.rd = (raw_instr >> 8) & 0xF;
    instr.rs1 = (raw_instr >> 4) & 0xF;
    instr.rs2 = raw_instr & 0xF;
    cpu->pc += 2;
    return instr;
}

// Execute instruction
void execute(CPU *cpu, Instruction instr) {
    switch (instr.opcode) {
        case ADD:
            cpu->registers[instr.rd] = cpu->registers[instr.rs1] + cpu->registers[instr.rs2];
            break;
        case SUB:
            cpu->registers[instr.rd] = cpu->registers[instr.rs1] - cpu->registers[instr.rs2];
            break;
        case AND:
            cpu->registers[instr.rd] = cpu->registers[instr.rs1] & cpu->registers[instr.rs2];
            break;
        case OR:
            cpu->registers[instr.rd] = cpu->registers[instr.rs1] | cpu->registers[instr.rs2];
            break;
        case XOR:
            cpu->registers[instr.rd] = cpu->registers[instr.rs1] ^ cpu->registers[instr.rs2];
            break;
        case SLL:
            cpu->registers[instr.rd] = cpu->registers[instr.rs1] << cpu->registers[instr.rs2];
            break;
        case SRL:
            cpu->registers[instr.rd] = cpu->registers[instr.rs1] >> cpu->registers[instr.rs2];
            break;
        case LDR:
            cpu->registers[instr.rd] = (cpu->memory[cpu->registers[instr.rs1]] << 24) |
                                       (cpu->memory[cpu->registers[instr.rs1] + 1] << 16) |
                                       (cpu->memory[cpu->registers[instr.rs1] + 2] << 8) |
                                       cpu->memory[cpu->registers[instr.rs1] + 3];
            break;
        case STR:
            cpu->memory[cpu->registers[instr.rd]] = (cpu->registers[instr.rs1] >> 24) & 0xFF;
            cpu->memory[cpu->registers[instr.rd] + 1] = (cpu->registers[instr.rs1] >> 16) & 0xFF;
            cpu->memory[cpu->registers[instr.rd] + 2] = (cpu->registers[instr.rs1] >> 8) & 0xFF;
            cpu->memory[cpu->registers[instr.rd] + 3] = cpu->registers[instr.rs1] & 0xFF;
            break;
        case BEQ:
            if (cpu->registers[instr.rs1] == cpu->registers[instr.rs2]) {
                cpu->pc = cpu->registers[instr.rd];
            }
            break;
        case HALT:
            printf("CPU Halted\n");
            exit(0);
        default:
            printf("Unknown opcode: %d\n", instr.opcode);
            exit(1);
    }
}

// Load program into memory
void load_program(CPU *cpu, uint16_t *program, int length) {
    for (int i = 0; i < length; i++) {
        cpu->memory[i * 2] = (program[i] >> 8) & 0xFF;
        cpu->memory[i * 2 + 1] = program[i] & 0xFF;
    }
}

// Print CPU state
void print_cpu_state(CPU *cpu) {
    printf("CPU State:\n");
    printf("PC: 0x%04X\n", cpu->pc);
    for (int i = 0; i < NUM_REGISTERS; i++) {
        printf("R%d: 0x%08X ", i, cpu->registers[i]);
        if ((i + 1) % 4 == 0) printf("\n");
    }
    printf("\n");
}

int main() {
    CPU cpu;
    init_cpu(&cpu);

    // Example program: Calculate (5 + 3) * 2
    uint16_t program[] = {
        (ADD << 12) | (1 << 8) | (0 << 4) | 0,    // ADD R1, R0, R0 (R1 = 0)
        (ADD << 12) | (1 << 8) | (1 << 4) | 1,    // ADD R1, R1, R1 (R1 = 5)
        (ADD << 12) | (1 << 8) | (1 << 4) | 1,    // ADD R1, R1, R1 (R1 = 5)
        (ADD << 12) | (1 << 8) | (1 << 4) | 0,    // ADD R1, R1, R0 (R1 = 5)
        (ADD << 12) | (2 << 8) | (0 << 4) | 0,    // ADD R2, R0, R0 (R2 = 0)
        (ADD << 12) | (2 << 8) | (2 << 4) | 2,    // ADD R2, R2, R2 (R2 = 3)
        (ADD << 12) | (2 << 8) | (2 << 4) | 0,    // ADD R2, R2, R0 (R2 = 3)
        (ADD << 12) | (1 << 8) | (1 << 4) | 2,    // ADD R1, R1, R2 (R1 = 8)
        (ADD << 12) | (3 << 8) | (1 << 4) | 1,    // ADD R3, R1, R1 (R3 = 16)
        (HALT << 12) | (0 << 8) | (0 << 4) | 0    // HALT
    };

    load_program(&cpu, program, sizeof(program) / sizeof(program[0]));

    printf("RISC CPU Simulation\n");
    printf("===================\n");

    while (1) {
        print_cpu_state(&cpu);
        Instruction instr = fetch(&cpu);
        execute(&cpu, instr);
    }

    return 0;
}