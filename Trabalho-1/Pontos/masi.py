def processar_pontos_geogebra(arquivo_entrada, arquivo_saida):
    """
    Processa arquivo do GeoGebra no formato:
    Nome, X, Y, Tipo
    E formata para uso em OpenGL/C
    """
    try:
        with open(arquivo_entrada, 'r', encoding='utf-8') as f:
            linhas = f.readlines()
        
        pontos_formatados = []
        
        # Pula o cabeçalho e processa a partir da segunda linha
        for i, linha in enumerate(linhas[1:], 1):  # Começa da linha 1 (pula cabeçalho)
            linha = linha.strip()
            
            # Pula linhas vazias
            if not linha:
                continue
                
            # Divide por vírgulas
            partes = linha.split(',')
            
            if len(partes) >= 3:
                nome = partes[0].strip()
                x = partes[1].strip()
                y = partes[2].strip()
                tipo = partes[3].strip() if len(partes) > 3 else "Desconhecido"
                
                # Converte para float e formata
                try:
                    x_float = float(x)
                    y_float = float(y)
                    
                    # Formata para C/OpenGL
                    ponto_formatado = f"    {{{x_float}f, {y_float}f}},  // {nome} ({tipo})"
                    pontos_formatados.append(ponto_formatado)
                    
                except ValueError:
                    print(f"Aviso: Valores inválidos na linha {i}: {linha}")
        
        # Escreve no arquivo de saída
        with open(arquivo_saida, 'w', encoding='utf-8') as f:
            f.write("// Pontos exportados do GeoGebra\n")
            f.write("// Formato: {x, y},  // Nome (Tipo)\n")
            f.write("Ponto2D pontosPersonagem[] = {\n")
            
            for ponto in pontos_formatados:
                f.write(ponto + '\n')
            
            f.write("};\n")
            f.write(f"int numPontosPersonagem = {len(pontos_formatados)};\n")
        
        print(f"✅ Processamento concluído!")
        print(f"📁 Entrada: {arquivo_entrada}")
        print(f"📁 Saída: {arquivo_saida}")
        print(f"📊 Total de pontos processados: {len(pontos_formatados)}")
        
        # Mostra estatísticas por tipo
        print(f"📈 Estatísticas:")
        tipos = {}
        for ponto in pontos_formatados:
            tipo = ponto.split('(')[-1].replace(')', '')
            tipos[tipo] = tipos.get(tipo, 0) + 1
        
        for tipo, quantidade in tipos.items():
            print(f"   - {tipo}: {quantidade} pontos")
        
        # Preview
        print(f"\n👀 Preview dos primeiros 10 pontos:")
        for i, ponto in enumerate(pontos_formatados[:10]):
            print(f"   {ponto}")
        
        if len(pontos_formatados) > 10:
            print(f"   ... e mais {len(pontos_formatados) - 10} pontos")
            
    except FileNotFoundError:
        print(f"❌ Erro: Arquivo '{arquivo_entrada}' não encontrado.")
    except Exception as e:
        print(f"❌ Erro ao processar arquivo: {e}")

# Versão alternativa que separa por tipo de objeto
def processar_por_tipo(arquivo_entrada, arquivo_saida):
    """
    Processa e separa pontos por tipo (Reta, Elipse, etc.)
    """
    try:
        with open(arquivo_entrada, 'r', encoding='utf-8') as f:
            linhas = f.readlines()
        
        pontos_por_tipo = {}
        
        for i, linha in enumerate(linhas[1:], 1):
            linha = linha.strip()
            if not linha:
                continue
                
            partes = linha.split(',')
            if len(partes) >= 3:
                nome = partes[0].strip()
                x = partes[1].strip()
                y = partes[2].strip()
                tipo = partes[3].strip() if len(partes) > 3 else "Nenhum"
                
                try:
                    x_float = float(x)
                    y_float = float(y)
                    
                    ponto_formatado = f"    {{{x_float}f, {y_float}f}},  // {nome}"
                    
                    if tipo not in pontos_por_tipo:
                        pontos_por_tipo[tipo] = []
                    
                    pontos_por_tipo[tipo].append(ponto_formatado)
                    
                except ValueError:
                    continue
        
        # Escreve arquivos separados por tipo
        for tipo, pontos in pontos_por_tipo.items():
            nome_arquivo = f"{arquivo_saida}_{tipo}.txt"
            
            with open(nome_arquivo, 'w', encoding='utf-8') as f:
                f.write(f"// Pontos do tipo: {tipo}\n")
                f.write(f"Ponto2D pontos{tipo}[] = {{\n")
                
                for ponto in pontos:
                    f.write(ponto + '\n')
                
                f.write("};\n")
                f.write(f"int numPontos{tipo} = {len(pontos)};\n")
            
            print(f"📄 Arquivo criado: {nome_arquivo} ({len(pontos)} pontos)")
        
    except Exception as e:
        print(f"❌ Erro: {e}")

# Execução principal
if __name__ == "__main__":
    arquivo_entrada = input("Nome do arquivo: ")
    arquivo_saida = input("Nome da saida formatada: ")
    
    print("🔄 Processando arquivo do GeoGebra...")
    processar_pontos_geogebra(arquivo_entrada, arquivo_saida)
    
    print(f"\n{'='*50}")
    print("🎯 Deseja também separar os pontos por tipo? (s/n)")
    resposta = input().strip().lower()
    
    if resposta == 's':
        print("🔄 Criando arquivos separados por tipo...")
        processar_por_tipo(arquivo_entrada, "pontos")
        print("✅ Arquivos separados criados!")