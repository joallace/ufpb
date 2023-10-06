def ler_input(file):
    f = open(file, "r")
    
    refs = [int(i) for i in f]
    n_quadros = refs.pop(0)

    f.close()

    return n_quadros, refs

def fifo(text_file):

    n_quadros, refs = ler_input(text_file)

    mudancas = 0
    quadros = ['vazio']*n_quadros
    idx = 0
    
    for i, ref in enumerate(refs):
        if ref in quadros:
            continue
        
        quadros[idx] = ref
        idx = (idx + 1) % n_quadros
        mudancas += 1

    return "FIFO " + str(mudancas)

def otm(text_file):

    n_quadros, refs = ler_input(text_file)

    mudancas = 0
    quadros = ['vazio']*n_quadros

    for i, ref in enumerate(refs):

        if ref in quadros:
            continue
        if 'vazio' in quadros:
            quadros[quadros.index('vazio')] = ref
            mudancas += 1
            continue

        pags = set(quadros)
        j = i + 1
        # Faz um set dos quadros na memória e percorre o restante das referências,
        # retirando do set o quadro que for encontrado. Quando restar apenas uma página
        # não encontrada, sabemos que ela será a referenciada por último e pode ser trocada
        while j < len(refs):
            if len(pags) <= 1:
                to_remove = list(pags)[0]
                break
            if refs[j] in pags:
                pags.remove(refs[j])
            j += 1
        else:
            #Caso mais de uma página não possua mais referências até o fim do programa,
            # o primeiro quadro que não será mais usado é escolhido para ser substituído
            for q in quadros:
                if q in pags:
                    to_remove = q
                    break

        # Quadro escolhido é removido
        mudancas += 1
        idx_remove = quadros.index(to_remove)
        quadros[idx_remove] = ref

    return "OTM " + str(mudancas)

def lru(text_file):

    n_quadros, refs = ler_input(text_file)

    mudancas = 0
    quadros = ['vazio']*n_quadros

    for i, ref in enumerate(refs):

        if ref in quadros:
            continue
        if 'vazio' in quadros:
            quadros[quadros.index('vazio')] = ref
            mudancas += 1
            continue

        pags = set(quadros)
        j = i - 1
        
        # Lógica semelhante ao ótimo, mas percorre as referências para trás, ao invés de para frente
        while j >= 0:
            if len(pags) <= 1:
                to_remove = list(pags)[0]
                break
            if refs[j] in pags:
                pags.remove(refs[j])
            j -= 1

        mudancas += 1
        idx_remove = quadros.index(to_remove)
        quadros[idx_remove] = ref

    return "LRU " + str(mudancas)

if __name__ == '__main__':
    response = ''
    response += fifo('inputs/in.txt') + '\n'
    response += otm('inputs/in.txt') + '\n'
    response += lru('inputs/in.txt')
    print(response)