# Sistema de Controle de Temperatura

* **Descrição do projeto:**
 
 O sistema foi projetado para controlar a temperatura de um ambiente, utilizando um controlador do tipo Proporcional. A interface do usuário é composta por um display LCD 16x2 e quatro botões de controle. O sistema contém algumas telas, tais como:
 * Main Screen: Mostra a temperatura desejada (setpoint), temperatura atual, estado do sistema (Driver, Heat e Fan como ON ou OFF).
 * New Set Point: Configura a nova temperatura desejada.
 * New Gain F e H: Configura o ganho do Fan e do Heat (ventilador e aquecedor).
 * Manual Mode: Override do driver para ativar ou o Fan ou o Heat manualmente.
 * Driver Status: Ativa ou desativa o controlador de calor.
 
  Além disso, existe um LED para indicação de funcionamento do driver (heartbeat). Quando o driver está ON, o led pisca a cada 500ms. Se o driver está OFF, o LED fica aceso indeterminadamente.
 
* **Fotos:**

<div align="center">
   <img src="proteus.png" alt="diagrama" width="50%" height="20%"/></center>
</div>
