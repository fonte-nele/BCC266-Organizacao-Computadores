import implementations.dm_kernel.user.JCL_FacadeImpl;
import interfaces.kernel.JCL_facade;

public class JCL_Tasks 
{
	public String switchOpcao1(Integer MAR, String MQ)
	{
		JCL_facade jcl = JCL_FacadeImpl.getInstance();
		
		String dados = jcl.getValue("memoriaDados_"+MAR.intValue()).getCorrectResult().toString();
		
		MQ = (dados + " esta jogando nesse momento.");
		
		System.out.println(MQ);
		System.out.println("END TASK 1");
		
		return MQ;
	}
	
	public String switchOpcao2(Integer MAR, String MQ)
	{
		JCL_facade jcl = JCL_FacadeImpl.getInstance();
		
		String dados = jcl.getValue("memoriaDados_"+MAR.intValue()).getCorrectResult().toString();
		
		MQ = (dados + " ganhou o jogo.");
		
		System.out.println(MQ);
		System.out.println("END TASK 2");
		
		return MQ;
	}
	
	public String switchOpcao3(Integer MAR, String MQ)
	{
		JCL_facade jcl = JCL_FacadeImpl.getInstance();
		
		String dados = jcl.getValue("memoriaDados_"+MAR.intValue()).getCorrectResult().toString();
		
		MQ = (dados + " perdeu o jogo.");
		
		System.out.println(MQ);
		System.out.println("END TASK 3");
		
		return MQ;
	}
	
	public String switchOpcao4(Integer MAR, String MQ)
	{
		JCL_facade jcl = JCL_FacadeImpl.getInstance();
		
		String dados = jcl.getValue("memoriaDados_"+MAR.intValue()).getCorrectResult().toString();
		
		MQ =(dados + " empatou o jogo.");
		
		System.out.println(MQ);
		System.out.println("END TASK 4");
		
		return MQ;
	}	
}