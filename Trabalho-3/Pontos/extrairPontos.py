import xml.etree.ElementTree as ET

# Arquivos
arquivo_xml = input("Nome do arquivo: ")
arquivo_saida = input("Nome da saida: ")

tree = ET.parse(arquivo_xml)
root = tree.getroot()

# ---------------------------
# 1. Identificar pontos que participam de comandos
pontos_reta = set()
pontos_elipse = set()

for cmd in root.iter('command'):
    nome_cmd = cmd.attrib.get('name')
    inputs = cmd.findall('input')
    if nome_cmd == 'Segment':
        for inp in inputs:
            for key in inp.attrib:
                pontos_reta.add(inp.attrib[key])
    elif nome_cmd == 'Ellipse':
        for inp in inputs:
            for key in inp.attrib:
                pontos_elipse.add(inp.attrib[key])

# ---------------------------
# 2. Ler todos os pontos
pontos = {}       # nome -> (x, y)
tipos = {}        # nome -> Tipo

for elem in root.iter('element'):
    etipo = elem.attrib.get('type')
    nome = elem.attrib.get('label')

    if etipo == 'point':
        coords = elem.find("coords")
        if coords is not None:
            try:
                x = float(coords.attrib.get("x", 0))
                y = float(coords.attrib.get("y", 0))
                pontos[nome] = (x, y)

                # Determinar tipo
                if nome in pontos_reta:
                    tipos[nome] = "Reta"
                elif nome in pontos_elipse:
                    tipos[nome] = "Elipse"
                else:
                    tipos[nome] = "Nenhum"
            except:
                pass

# ---------------------------
# 3. Escrever arquivo de saÃda mantendo ordem do XML
with open(arquivo_saida, "w") as f:
    f.write("Nome, X, Y, Tipo\n")
    for elem in root.iter('element'):
        etipo = elem.attrib.get('type')
        nome = elem.attrib.get('label')
        if etipo == 'point' and nome in pontos:
            x, y = pontos[nome]
            f.write(f"{nome}, {x}, {y}, {tipos[nome]}\n")

print(f"Arquivo '{arquivo_saida}' gerado com sucesso!")