NAME=ansible
URL=https://docs.ansible.com/ansible/latest/modules/list_of_all_modules.html

main: modules.xml

modules.xml: modules.h.xml  
	@xsl modules.xsl $< $@
	
modules.h.xml: modules.html  
	@cp $< $@
	@sed -i '3896d' $@
	@sed -i '3861d' $@
	@sed -i '92,94d' $@
	@sed -i '77d' $@
	@sed -i '62d' $@
	@sed -i '49d' $@
	@sed -i '48d' $@
	@sed -i '9d' $@
	@sed -i '7d' $@
	@sed -i '/DOCTYPE html/d' $@
	@sed -i '/---/d' $@
	@sed -i 's/ & / \&amp; /g' $@
	@sed -i 's/ && / \&amp;\&amp; /g' $@
	@sed -i 's/ &mdash; / - /g' $@
	@sed -i 's/ &raquo;/ /g' $@
	@sed -i 's/ &copy;/ /g' $@
# line 6,8,47,48,60,90:  <>=>< />
#	
	
modules.html: 
	wget ${URL} -O $@

	
clean:
	${RM} modules.xml
	${RM} modules.h.xml
	
cleanall: clean
	${RM} modules.mk
