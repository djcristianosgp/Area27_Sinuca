import os

def build_webpages(data_dir, output_h):
    print(f"Buscando arquivos em: {data_dir}")
    
    html_files = {
        'index.html': 'HTML_INDEX',
        'players.html': 'HTML_PLAYERS',
        'match.html': 'HTML_MATCH',
        'ranking.html': 'HTML_RANKING',
        'settings.html': 'HTML_SETTINGS',
        'about.html': 'HTML_ABOUT',
        'tv.html': 'HTML_TV',
        'profile.html': 'HTML_PROFILE',
        'hall.html': 'HTML_HALL',
        'championship.html': 'HTML_CHAMPIONSHIP',
        'wifi.html': 'HTML_WIFI_CONFIG'
    }
    
    css_files = {
        'style.css': 'CSS_STYLE'
    }
    
    js_files = {
        'app.js': 'JS_APP',
        'api.js': 'JS_API'
    }
    
    with open(output_h, 'w', encoding='utf-8') as f_out:
        f_out.write('#ifndef WEBPAGES_H\n')
        f_out.write('#define WEBPAGES_H\n\n')
        f_out.write('#include <Arduino.h>\n\n')
        
        # HTML Files
        for filename, varname in html_files.items():
            filepath = os.path.join(data_dir, filename)
            if os.path.exists(filepath):
                with open(filepath, 'r', encoding='utf-8') as f_in:
                    content = f_in.read()
                    f_out.write(f'const char {varname}[] PROGMEM = R"=====(\n{content}\n)=====";\n\n')
            else:
                print(f"Aviso: {filename} não encontrado!")
                
        # CSS Files
        for filename, varname in css_files.items():
            filepath = os.path.join(data_dir, filename)
            if os.path.exists(filepath):
                with open(filepath, 'r', encoding='utf-8') as f_in:
                    content = f_in.read()
                    f_out.write(f'const char {varname}[] PROGMEM = R"=====(\n{content}\n)=====";\n\n')
            else:
                print(f"Aviso: {filename} não encontrado!")
                
        # JS Files
        for filename, varname in js_files.items():
            filepath = os.path.join(data_dir, filename)
            if os.path.exists(filepath):
                with open(filepath, 'r', encoding='utf-8') as f_in:
                    content = f_in.read()
                    f_out.write(f'const char {varname}[] PROGMEM = R"=====(\n{content}\n)=====";\n\n')
            else:
                print(f"Aviso: {filename} não encontrado!")
                
        f_out.write('#endif // WEBPAGES_H\n')
        print(f"{output_h} gerado com sucesso!")

if __name__ == "__main__":
    current_dir = os.path.dirname(os.path.abspath(__file__))
    data_dir = os.path.join(current_dir, '..', 'data', 'www')
    output_h = os.path.join(current_dir, '..', 'WebPages.h')
    
    # Executa quando rodado no root do projeto via pio ou manualmente
    if not os.path.exists(data_dir):
        data_dir = os.path.join(current_dir, 'data', 'www')
        output_h = os.path.join(current_dir, 'WebPages.h')
        
    build_webpages(data_dir, output_h)
