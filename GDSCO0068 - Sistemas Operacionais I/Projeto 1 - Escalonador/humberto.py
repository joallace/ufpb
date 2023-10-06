
def ler_input(file):
    f = open(file, "r")
    fila = []
    for processo in f:
        tempos = processo.split()
        fila.append({'t_chegada':int(tempos[0]),'t_pico':int(tempos[1])})
    f.close()

    return fila


def sjf(text_file):

    fila = ler_input(text_file)

    t_espera = []
    t_retorno = []

    seg_atual = 0
    idx = 0
    
    while len(fila) > 0:
        t_menor = fila[0]['t_pico']
        menor_cheg = fila[0]['t_chegada']
        idx_menor = 0
        p_possivel = False

        # Percorrendo todos os processos para achar o com menor de tempo de processamento
        for idx, p in enumerate(fila):
            # Se o segundo atual é menor que o tempo de chegada do processo, ele não pode ser escolhido
            if p['t_chegada'] > seg_atual:
                menor_cheg = min(menor_cheg,p['t_chegada'])
                continue

            p_possivel = True
            if p['t_pico'] < t_menor:
                t_menor = p['t_pico']
                idx_menor = idx

        # Se nenhum processo estiver disponível no segundo atual, muda o segundo atual para o da chegada do próximo processo
        if not p_possivel:
            seg_atual = menor_cheg
            continue

        # Calcula o tempo de espera (Segundo atual menos chegada) e de retorno (Adiciona o tempo de pico e faz o mesmo cálculo)
        # Tempo de resposta é o mesmo que o de espera, já que não há preempção
        t_espera.append(seg_atual - fila[idx_menor]['t_chegada'])
        seg_atual += fila[idx_menor]['t_pico']
        t_retorno.append(seg_atual - fila[idx_menor]['t_chegada'])
        fila.pop(idx_menor)

    ret_medio = sum(t_retorno)/len(t_retorno)
    esp_medio = sum(t_espera)/len(t_espera)
    return "SJF " + "{:.1f} ".format(ret_medio) + "{:.1f} ".format(esp_medio) + "{:.1f}".format(esp_medio)

def fcfs(text_file):

    fila = ler_input(text_file)

    t_espera = []
    t_retorno = []

    seg_atual = 0
    idx = 0
    
    while len(fila) > 0:
        t_menor = fila[0]['t_chegada']
        idx_menor = 0
        p_possivel = False

        # Percorre a fila de processos para encontrar o com menor tempo de chegada
        for idx, p in enumerate(fila):
            if p['t_chegada'] > seg_atual:
                continue
            
            p_possivel = True
            if p['t_chegada'] < t_menor:
                t_menor = p['t_chegada']
                idx_menor = idx

        # Caso nenhum processo possa ser adicionado no segundo atual (Mesma lógica que o SJF)
        if not p_possivel:
            seg_atual = t_menor
            continue

        t_espera.append(seg_atual - fila[idx_menor]['t_chegada'])
        seg_atual += fila[idx_menor]['t_pico']
        t_retorno.append(seg_atual - fila[idx_menor]['t_chegada'])
        fila.pop(idx_menor)

    ret_medio = sum(t_retorno)/len(t_retorno)
    esp_medio = sum(t_espera)/len(t_espera)
    return "FCFS " + "{:.1f} ".format(ret_medio) + "{:.1f} ".format(esp_medio) + "{:.1f}".format(esp_medio)

def rr(text_file):

    fila = ler_input(text_file)
    
    # Ordena a fila de processos em relação ao tempo de chegada
    fila = sorted(fila, key=lambda d: d['t_chegada'])

    t_espera = []
    t_retorno = []
    t_resposta = []

    seg_atual = 0
    idx = 0
    quantum = 2

    # Adiciona duas variáveis para calcular os tempos de resposta e de espera, respectivamente
    for i, p in enumerate(fila):
        fila[i]['resp'] = False
        fila[i]['pico_org'] = fila[i]['t_pico']

    while len(fila) > 0:
        # Caso o tempo de chegada do processo em primeiro lugar na fila não tenha chegado ainda
        if seg_atual < fila[0]['t_chegada']:
            idx = 0
            # Tenta encontrar um processo na fila com tempo de chegada menor que o segundo atual
            while idx < len(fila) and seg_atual < fila[idx]['t_chegada']:
                idx += 1
            # Caso encontre, o coloca no primeiro lugar da fila
            if idx < len(fila):
                fila.insert(0,fila.pop(idx))
            # Caso não, muda o segundo atual para o tempo de chegada do primeiro lugar da fila
            else:
                seg_atual = fila[0]['t_chegada']

        # Verifica se esse processo já foi processado previamente e calcula o tempo de resposta dele
        if not fila[0]['resp']:
            t_resposta.append(seg_atual - fila[0]['t_chegada'])
            fila[0]['resp'] = True

        # Calcula o tempo de processamento, e diminui esse valor do tempo de pico restante do processo
        t_process = min(quantum,fila[0]['t_pico'])
        seg_atual += t_process
        fila[0]['t_pico'] -= t_process

        # Caso o processo não tenha terminado, o coloca de volta no final da fila de processos disponíveis no segundo atual
        # (Antes do primeiro processo com tempo de chegada maior que o segundo atual)
        if fila[0]['t_pico'] > 0:
            idx = 0
            while idx < len(fila) and fila[idx]['t_chegada'] <= seg_atual:
                idx += 1
            
            to_insert = fila[0]
            fila.insert(idx,to_insert)
            fila.pop(0)
        # Caso contrário, remove o processo da fila e calcula seu tempo de retorno e de espera
        else:
            t_retorno.append(seg_atual - fila[0]['t_chegada'])
            t_espera.append(seg_atual - fila[0]['pico_org'] - fila[0]['t_chegada'])
            fila.pop(0)

    ret_medio = sum(t_retorno)/len(t_retorno)
    esp_medio = sum(t_espera)/len(t_espera)
    resp_medio = sum(t_resposta)/len(t_resposta)
    return "RR " + "{:.1f} ".format(ret_medio) + "{:.1f} ".format(resp_medio) + "{:.1f}".format(esp_medio) 

if __name__ == '__main__':
    response = ''
    path = 'inputs/ex4.txt'
    response += fcfs(path).replace(".", ",") + '\n'
    response += sjf(path).replace(".", ",") + '\n'
    response += rr(path).replace(".", ",")
    print(response)