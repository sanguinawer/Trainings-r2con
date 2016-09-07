import r2pipe
import sys
import json
inputfile = sys.argv[1]
outputfile = sys.argv[2]
maxSteps= 50000
r2 = r2pipe.open(inputfile)
r2.cmd('e io.cache=true');
r2.cmd('e asm.bits=32');
r2.cmd('aei');
r2.cmd('aeim');
r2.cmd('aer esp=0x00108000');
r2.cmd('.ar*');
steps = 0;
lastFpu = 0;
lastLoop = 0;
while(1):
        try:
           cop = r2.cmdj('pdj 1 @ eip')[0];
           regs = r2.cmdj('arj');
        except:
           print "error"
           break;
        data = json.dumps(cop)
        decode = json.loads(data)
        cop_type = str(decode["type"])
        cop_offset = str(decode["offset"])
        cop_opcode = str(decode["opcode"])
        cop_bytes = str(decode["bytes"])
        data = json.dumps(regs)
        decode = json.loads(data)
        regs_ecx = str(decode["ecx"])
        # print cop_type,cop_offset,cop_opcode,cop_bytes,regs_ecx
        # Check for end of shellcode or invalid opcode */
        if 'int ' in cop_opcode or 'invalid' in cop_type: 
             r2.cmd('e asm.comments=false');
             r2.cmd('e asm.lines=false');
             r2.cmd('e asm.flags=false');
         
             j = r2.cmdj('oj')[0]
             data = json.dumps(j)
             decode = json.loads(data)
             end = int(decode["size"])
             start = int(lastLoop)
             dissas = r2.cmd('pD ' + str(end-start) + ' @ ' + str(start));
             print dissas
             break;
        # Emulate fpu opcodes */
        if cop_opcode[0]=='f'  and cop_bytes[0]=='d':
             if 'fnstenv' in cop_opcode:
                 r2.cmd('wv ' + lastFpu + ' @ esp')
             else:
                 lastFpu = cop_offset
        #Check for end of loop opcodes */
        if 'loop' in cop_opcode and int(regs_ecx) <= 1:
             lastLoop = int(cop_offset) + 2
        r2.cmd('aes')
        #Limit the steps to avoid infinite loops */
        steps = steps + 1
        if steps >= maxSteps:
             print("Maximum steps reached. Exiting.")
             break;

