//import java.io.File;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

import implementations.dm_kernel.user.JCL_FacadeImpl;
import interfaces.kernel.JCL_facade;
import interfaces.kernel.JCL_result;

/*
	Feito por: Felipe Fontenele de Avila Magalhaes
	Matricula: 15.1.4331
	Materia: BCC 266 - Organizacao de Computadores.
	Prof.: Joubert Castro Lima
*/
public class Principal
{	
	private JCL_facade jcl;
	private int num_memory = 0;
	private static int num_inst = 100;
	private static int num_opc = 3;
	private static int num_dados = 20;
	
	
	public static void main(String[] args)
	{			
		new Principal();
	}
	
	public Principal()
	{
	
		/*Opcode das instrucoes:
		0 : Jogar jogo;
		1 : Ganhar jogo;
		2 : Perder jogo;
		3 : Empatar jogo;
		4 : Terminar o programa.*/
			
		jcl = JCL_FacadeImpl.getInstance(); //Serve para instanciar JCL (versoes lambari e pacu)
		
		montarMemoriaInst();
		
		montarMemoriaDados();
		
		int PC = 0;   //Contador de programa!!!
		int IR = -1;  //Registrador de instrucao!!! 
		int MAR = -1; //Registrador de endereco de memoria!!!
		String MBR = "";
		String MQ = "";
		
		Boolean b = jcl.register(JCL_Tasks.class, "JCL_Tasks");
		System.err.println(b);
		
		List<String> tickets = new LinkedList<String>(); //Lista de tickets para as maquinas!!!
				
		System.out.println("Inicializando a simulacao !!!");
		while (IR!=4)
		{
			MBR = jcl.getValue("memoriaInst_"+PC).getCorrectResult().toString(); //Recebe a memoria de instrucao na posicao do contador do programa!!!
			
			String[] aux = MBR.split(":");  //Divisao do registrador de instrucao e do registrador de endereco de memoria!!!
			
			IR = Integer.parseInt(aux[0]); //Conversao de string para inteiro!!
			MAR = Integer.parseInt(aux[1]);//Conversao de string para inteiro!!
			
			switch (IR)
			{
				case 0:
				{
					Object[] args ={new Integer(MAR),MQ};
					String ticket = jcl.execute("JCL_Tasks", "switchOpcao1", args); //Tickets
					JCL_result jclr = jcl.getResultBlocking(ticket);
					MQ = jclr.getCorrectResult().toString();
					jcl.instantiateGlobalVar("memory_"+PC,MQ);
					num_memory += 1;
					//System.out.println(MQ);
					tickets.add(ticket);
					break;
				}
				case 1:
				{
					Object[] args ={new Integer(MAR),MQ};
					String ticket = jcl.execute("JCL_Tasks", "switchOpcao2", args);
					JCL_result jclr = jcl.getResultBlocking(ticket);
					MQ = jclr.getCorrectResult().toString();
					jcl.instantiateGlobalVar("memory_"+PC,MQ);
					num_memory += 1;
					//System.out.println(MQ);
					tickets.add(ticket);
					break;
				}
				case 2:
				{
					Object[] args ={new Integer(MAR),MQ};
					String ticket = jcl.execute("JCL_Tasks", "switchOpcao3", args);
					JCL_result jclr = jcl.getResultBlocking(ticket);
					MQ = jclr.getCorrectResult().toString();
					jcl.instantiateGlobalVar("memory_"+PC,MQ);
					num_memory += 1;
					//System.out.println(MQ);
					tickets.add(ticket);
					break;
				}
				case 3:
				{
					Object[] args ={new Integer(MAR), MQ};
					String ticket = jcl.execute("JCL_Tasks", "switchOpcao4", args);
					JCL_result jclr = jcl.getResultBlocking(ticket);
					MQ = jclr.getCorrectResult().toString();
					jcl.instantiateGlobalVar("memory_"+PC,MQ);
					num_memory += 1;
					//System.out.println(MQ);
					tickets.add(ticket);
					break;
				}
			}	
			PC++;
		}
		
		//Coletar os resultados remanescentes!!! 
		for(String str:tickets)
		{
			JCL_result soma = jcl.getResultBlocking(str);
		}
		
		for(int i=0; i<num_memory; i++)
		{
			System.out.println(jcl.getValue("memory_"+i).getCorrectResult().toString());
		}
		
		System.out.println("Finalizando a simulacao !!!");
		
		jcl.destroy();
	}
	
	private void montarMemoriaInst()
	{
		//Preenchimento memoria de instrucoes aleatoriamente!!!
		Random random = new Random();
		int i;
		
		for(i=0; i<num_inst; i++)
		{
			int opcode = random.nextInt(num_opc);
			int mar = random.nextInt(num_dados);
			jcl.instantiateGlobalVar("memoriaInst_"+i, opcode+":"+mar);
		}
		jcl.instantiateGlobalVar("memoriaInst_"+i, "4:-1");
	}
	
	private void montarMemoriaDados()
	{
		//Preenchimento memoria de dados manualmente!!!
		jcl.instantiateGlobalVar(("memoriaDados_0"), "Atletico-MG");
		jcl.instantiateGlobalVar(("memoriaDados_1"), "Atletico-PR");
		jcl.instantiateGlobalVar(("memoriaDados_2"), "Avai");
		jcl.instantiateGlobalVar(("memoriaDados_3"), "Chapecoense");
		jcl.instantiateGlobalVar(("memoriaDados_4"), "Corinthians");
		jcl.instantiateGlobalVar(("memoriaDados_5"), "Coritiba");
		jcl.instantiateGlobalVar(("memoriaDados_6"), "Cruzeiro");
		jcl.instantiateGlobalVar(("memoriaDados_7"), "Figueirense");
		jcl.instantiateGlobalVar(("memoriaDados_8"), "Flamengo");
		jcl.instantiateGlobalVar(("memoriaDados_9"), "Fluminense");
		jcl.instantiateGlobalVar(("memoriaDados_10"), "Goias");
		jcl.instantiateGlobalVar(("memoriaDados_11"), "Gremio");
		jcl.instantiateGlobalVar(("memoriaDados_12"), "Internacional");
		jcl.instantiateGlobalVar(("memoriaDados_13"), "Joinville");
		jcl.instantiateGlobalVar(("memoriaDados_14"), "Palmeiras");
		jcl.instantiateGlobalVar(("memoriaDados_15"), "Ponte Preta");
		jcl.instantiateGlobalVar(("memoriaDados_16"), "Santos");
		jcl.instantiateGlobalVar(("memoriaDados_17"), "Sao Paulo");
		jcl.instantiateGlobalVar(("memoriaDados_18"), "Sport");
		jcl.instantiateGlobalVar(("memoriaDados_19"), "Vasco");
	}
}