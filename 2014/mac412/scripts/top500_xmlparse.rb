##################################################################################
#Top500.org XML parse
#
#Coded by: Fellipe Souto <fllsouto@gmail.com>
#
# To run:
# $ruby top500_xmlparse.rb <somecountryname>
#
# tip: The country name is optional
##################################################################################


require 'rexml/document'
require 'yaml'
include REXML #create an REXML namespace

def extract_elements(xmldoc,path=nil)
	list = []
	xmldoc.elements.each(path) do |e|
		list << e 
	end
	list
end

def get_text(e,child,head="top500:")
	unless e.get_text("#{head}#{child}").nil?
		e.get_text("#{head}#{child}")
	else
		"Unknown"
	end
end

def get_params(e)
	{
		rank: get_text(e,"rank"),
		name: get_text(e,"system-name"),
		computer: get_text(e,"computer"),
		cores: get_text(e,"number-of-processors"),
		rmax: get_text(e,"r-max"),
		rpeak: get_text(e,"r-peak"),
		country: get_text(e,"country"),
		town: get_text(e,"town"),
	}
end

def get_list(original_list,country=nil)
	newList = []
	original_list.each do |e|
		unless country.nil?
			if get_text(e,"country") == country
				newList.push(get_params(e))
			end
		else
			newList.push(get_params(e))
		end
	end
	newList
end

def format_output(e)
	"Rank : #{e[:rank]}\nName #{e[:name]}\nComputer : #{e[:computer]}\nCores : #{e[:cores]}\nRmax : #{e[:rmax]}\nRpeak : #{e[:rpeak]}\nCountry : #{e[:country]}\nTown : #{e[:town]}\n\n"
end

def root_info(xml)
	root = xml.root
	puts "Root element : " + "\nURL : " + root.attributes["xmlns:top500"] + "\nAuthors : " + root.attributes["authors"] + "\nDate : " + root.attributes["date"] 
end

def show_list(country,list)
	puts "Lista de computadores mais rápidos do mundo"
	puts "País : " + ((country.nil?)? "Todo o mundo" : country)
	puts "Total de computadores encontrados : #{list.size}\n"
	list.each do |e|
		puts format_output(e)
	end
end

country = !(ARGV[0].nil?)? ARGV[0].capitalize : nil
xmlfile = File.new("TOP500_201406_all.xml")
xmldoc = Document.new(xmlfile)
#or xmldoc = REXML::Document.new xmlfile if you don't like to create an scope

computers = extract_elements(xmldoc,"top500:list/top500:site")
list = get_list(computers,country)
show_list(country,list)
